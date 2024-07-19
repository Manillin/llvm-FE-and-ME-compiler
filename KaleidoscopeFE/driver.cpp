#include "driver.hpp"
#include "parser.hpp"

// check update

/**
 * @brief Extra notions:
 *
 * + Value* -> valore in LLVM IR : variabile, costante, istruzione
 * + drv.NamedValues[] -> contiene le variabili relative allo scope attuale.
 * + createInBoundsGEP -> GetElementPointer (inBounds granted), calcola l'indirizzo di un elemento di un array
 *
 *
 * + (*module) -> tutte le funzioni, variabili globali e definizioni di tipo vengono qui raccolte e organizzate
 * + (*context) -> contenitore per tutti i dati globali usati durante la generazione del codice LLVM
 * + (*builder) -> strumento (helper) per costruire facilmente istruzioni LLVM IR
 *
 */

// Generazione di un'istanza per ciascuna della classi LLVMContext,
// Module e IRBuilder. Nel caso di singolo modulo è sufficiente
LLVMContext *context = new LLVMContext;

/** @param *module
 *  rappresenta l'unità di compilazione principale del codice LLVM.
 * È qui che tutte le funzioni, variabili globali e definizioni di tipo vengono raccolte e organizzate.
 */

Module *module = new Module("Kaleidoscope", *context);
IRBuilder<> *builder = new IRBuilder(*context);

Value *LogErrorV(const std::string Str)
{
  std::cerr << Str << std::endl;
  return nullptr;
}
/* Il codice seguente sulle prime non è semplice da comprendere.
   Esso definisce una utility (funzione C++) con due parametri:
   1) la rappresentazione di una funzione llvm IR, e
   2) il nome per un registro SSA
   La chiamata di questa utility restituisce un'istruzione IR che alloca un double
   in memoria e ne memorizza il puntatore in un registro SSA cui viene attribuito
   il nome passato come secondo parametro. L'istruzione verrà scritta all'inizio
   dell'entry block della funzione passata come primo parametro.
   Si ricordi che le istruzioni sono generate da un builder. Per non
   interferire con il builder globale, la generazione viene dunque effettuata
   con un builder temporaneo TmpB
*/
static AllocaInst *CreateEntryBlockAlloca(Function *fun, StringRef VarName, Type *type = Type::getDoubleTy(*context))
{
  IRBuilder<> TmpB(&fun->getEntryBlock(), fun->getEntryBlock().begin());
  return TmpB.CreateAlloca(type, nullptr, VarName);
}

// Implementazione del costruttore della classe driver
driver::driver() : trace_parsing(false), trace_scanning(false){};

// Implementazione del metodo parse
int driver::parse(const std::string &f)
{
  file = f;                              // File con il programma
  location.initialize(&file);            // Inizializzazione dell'oggetto location
  scan_begin();                          // Inizio scanning (ovvero apertura del file programma)
  yy::parser parser(*this);              // Istanziazione del parser
  parser.set_debug_level(trace_parsing); // Livello di debug del parsed
  int res = parser.parse();              // Chiamata dell'entry point del parser
  scan_end();                            // Fine scanning (ovvero chiusura del file programma)
  return res;
}

// Implementazione del metodo codegen, che è una "semplice" chiamata del
// metodo omonimo presente nel nodo root (il puntatore root è stato scritto dal parser)
void driver::codegen()
{
  root->codegen(*this);
};

/************************* Sequence tree **************************/
SeqAST::SeqAST(RootAST *first, RootAST *continuation) : first(first), continuation(continuation){};

// La generazione del codice per una sequenza è banale:
// mediante chiamate ricorsive viene generato il codice di first e
// poi quello di continuation (con gli opportuni controlli di "esistenza")
Value *SeqAST::codegen(driver &drv)
{
  if (first != nullptr)
  {
    Value *f = first->codegen(drv);
  }
  else
  {
    if (continuation == nullptr)
      return nullptr;
  }
  Value *c = continuation->codegen(drv);
  return nullptr;
};

/********************* Number Expression Tree *********************/
NumberExprAST::NumberExprAST(double Val) : Val(Val){};

lexval NumberExprAST::getLexVal() const
{
  // Non utilizzata, Inserita per continuità con versione precedente
  lexval lval = Val;
  return lval;
};

// Non viene generata un'struzione; soltanto una costante LLVM IR
// corrispondente al valore float memorizzato nel nodo
// La costante verrà utilizzata in altra parte del processo di generazione
// Si noti che l'uso del contesto garantisce l'unicità della costanti
Value *NumberExprAST::codegen(driver &drv)
{
  return ConstantFP::get(*context, APFloat(Val));
};

/*******************************************************************\
 * Variable Expression Tree
 * Rappresenta la risoluzione di una variabile (può essere globale o locale)
 *
 *
 * exp: %name = load double, double* %addr, align 8
 *********************************************************************/
VariableExprAST::VariableExprAST(const std::string &Name, ExprAST *Exp, bool isArray) : Name(Name), Exp(Exp), isArray(isArray){};

lexval VariableExprAST::getLexVal() const
{
  lexval lval = Name;
  return lval;
};

Value *VariableExprAST::codegen(driver &drv)
{
  AllocaInst *A = drv.NamedValues[Name];
  //* controllo scope globale se non è stata trovata nell'ambiente locale
  if (!A)
  {
    GlobalVariable *globVar = module->getNamedGlobal(Name);
    if (!globVar)
      return LogErrorV("Variabile non definita: " + Name);
    //* logica array globale
    if (isArray)
    {
      Value *Val = Exp->codegen(drv); //* valore dell'indice dell'array
      if (!Val)
        return nullptr;
      //* calcolo indice array per la load
      Value *floatIndex = builder->CreateFPTrunc(Val, Type::getFloatTy(*context));
      Value *intIndex = builder->CreateFPToSI(floatIndex, Type::getInt32Ty(*context));
      Value *cell = builder->CreateInBoundsGEP(globVar->getValueType(), globVar, intIndex);
      return builder->CreateLoad(Type::getDoubleTy(*context), cell, Name.c_str());
    }
    return builder->CreateLoad(globVar->getValueType(), globVar, Name.c_str()); // c_str() ottiene rappresentazione C della stringa (array di char)
  }
  if (isArray)
  {
    //* logica array locale - come sopra
    Value *Val = Exp->codegen(drv);
    if (!Val)
      return nullptr;
    Value *floatIndex = builder->CreateFPTrunc(Val, Type::getFloatTy(*context));
    Value *intIndex = builder->CreateFPToSI(floatIndex, Type::getInt32Ty(*context));
    Value *cell = builder->CreateInBoundsGEP(A->getAllocatedType(), A, intIndex);
    return builder->CreateLoad(Type::getDoubleTy(*context), cell, Name.c_str());
  }
  //* trovata nello scope locale, generazione streamlined
  return builder->CreateLoad(A->getAllocatedType(), A, Name.c_str());
}

/******************** Binary Expression Tree **********************/
BinaryExprAST::BinaryExprAST(char Op, ExprAST *LHS, ExprAST *RHS) : Op(Op), LHS(LHS), RHS(RHS){};

//*****NEW*****/
// La generazione del codice in questo caso è di facile comprensione.
// Vengono ricorsivamente generati il codice per il primo e quello per il secondo
// operando. Con i valori memorizzati in altrettanti registri SSA si
// costruisce l'istruzione utilizzando l'opportuno operatore
Value *BinaryExprAST::codegen(driver &drv)
{
  if (Op == 'n')
  {
    Value *R = RHS->codegen(drv);
    if (!R)
      return nullptr;
    return builder->CreateNot(R, "notres");
  }
  Value *L = LHS->codegen(drv);
  Value *R = RHS->codegen(drv);
  if (!L || !R)
    return nullptr;
  switch (Op)
  {
  case '+':
    return builder->CreateFAdd(L, R, "addres");
  case '-':
    return builder->CreateFSub(L, R, "subres");
  case '*':
    return builder->CreateFMul(L, R, "mulres");
  case '/':
    return builder->CreateFDiv(L, R, "addres");
  case '<':
    return builder->CreateFCmpULT(L, R, "lttest");
  case '>':
    return builder->CreateFCmpUGT(L, R, "gttest");
  case '=':
    return builder->CreateFCmpUEQ(L, R, "eqtest");
  case 'a':
    return builder->CreateLogicalAnd(L, R, "andres");
  case 'o':
    return builder->CreateLogicalOr(L, R, "orres");
  default:
    std::cout << Op << std::endl;
    return LogErrorV("Operatore binario non supportato");
  }
};

/********************* Call Expression Tree ***********************/
/* Call Expression Tree */
CallExprAST::CallExprAST(std::string Callee, std::vector<ExprAST *> Args) : Callee(Callee), Args(std::move(Args)){};

lexval CallExprAST::getLexVal() const
{
  lexval lval = Callee;
  return lval;
};

Value *CallExprAST::codegen(driver &drv)
{
  // La generazione del codice corrispondente ad una chiamata di funzione
  // inizia cercando nel modulo corrente (l'unico, nel nostro caso) una funzione
  // il cui nome coincide con il nome memorizzato nel nodo dell'AST
  // Se la funzione non viene trovata (e dunque non è stata precedentemente definita)
  // viene generato un errore
  Function *CalleeF = module->getFunction(Callee);
  if (!CalleeF)
    return LogErrorV("Funzione non definita");
  // Il secondo controllo è che la funzione recuperata abbia tanti parametri
  // quanti sono gi argomenti previsti nel nodo AST
  if (CalleeF->arg_size() != Args.size())
    return LogErrorV("Numero di argomenti non corretto");
  // Passato con successo anche il secondo controllo, viene predisposta
  // ricorsivamente la valutazione degli argomenti presenti nella chiamata
  // (si ricordi che gli argomenti possono essere espressioni arbitarie)
  // I risultati delle valutazioni degli argomenti (registri SSA, come sempre)
  // vengono inseriti in un vettore, dove "se li aspetta" il metodo CreateCall
  // del builder, che viene chiamato subito dopo per la generazione dell'istruzione
  // IR di chiamata
  std::vector<Value *> ArgsV;
  for (auto arg : Args)
  {
    ArgsV.push_back(arg->codegen(drv));
    if (!ArgsV.back())
      return nullptr;
  }
  return builder->CreateCall(CalleeF, ArgsV, "calltmp");
}

/************************* IF expression *************************/
IfExprAST::IfExprAST(ExprAST *cond, ExprAST *trueexp, ExprAST *falseexp) : cond(cond), trueexp(trueexp), falseexp(falseexp){};

/*****Removed comments from original source code*****/
Value *IfExprAST::codegen(driver &drv)
{
  Value *CondV = cond->codegen(drv);
  if (!CondV)
    return nullptr;

  Function *fun = builder->GetInsertBlock()->getParent();
  BasicBlock *TrueBB = BasicBlock::Create(*context, "trueblock", fun);
  /*
   * Non può stare dietro al blocco true perchè non abbiamo ancora creato il body
   * del blocco true, nel quale in cui non sappiamo ancora cosa succede.
   * Allora creiamo un blocco senza dargli un riferimento dove metterlo.
   */
  BasicBlock *FalseBB = BasicBlock::Create(*context, "falseblock");
  BasicBlock *MergeBB = BasicBlock::Create(*context, "mergeblock");
  /*
   * Creazione dell'istruzione di branch nel caso di condizione vera e falsa
   */
  builder->CreateCondBr(CondV, TrueBB, FalseBB);
  /*
   * Per generare il body della condizione true, devo settare il builder per scrivere nel blocco
   * di True, poi abbiamo generato il codice per il blocco true
   */
  builder->SetInsertPoint(TrueBB);
  Value *trueV = trueexp->codegen(drv);
  if (!trueV)
    return nullptr;
  /**
   * A questo punto possiamo mettere il branch al merge.
   * il merge block abbiamo questa istruzione phi
   * Se il blocco true non si è ulteriormente spezzato, rimango lì e  non fa nulla
   * se invece si è spezzato, devo inserire il salto dall'ultimo blocco per inserirla nel phi.
   */
  TrueBB = builder->GetInsertBlock();

  builder->CreateBr(MergeBB);
  fun->insert(fun->end(), FalseBB);
  // false expr
  builder->SetInsertPoint(FalseBB);
  Value *falseV = falseexp->codegen(drv);
  if (!falseV)
    return nullptr;

  FalseBB = builder->GetInsertBlock();
  builder->CreateBr(MergeBB);

  fun->insert(fun->end(), MergeBB);
  builder->SetInsertPoint(MergeBB);

  PHINode *P = builder->CreatePHI(Type::getDoubleTy(*context), 2);
  P->addIncoming(trueV, TrueBB);
  P->addIncoming(falseV, FalseBB);
  return P;
};

/*******************************************************************\
 * Block Tree
 * Rappresenta un blocco di codice, cioè una sequenza di istruzioni
 * Specializza (sostituendo) la classe BlockExprAST
 *
 * Un blocco è un espressione preceduto da definizioni di variabili
 *
 * Gestisce le definizioni di variabili e una serie di statements ( todo: check array )
 *
 * Gestisce anche lo scope delle variabili:
 *  - quando crea un nuovo blocco di codice, salva la symbol table corrente
 *  - genera le istruzioni e modofica la symbol table
 *  - ripristina la symbol table al termine del blocco per avere la visibilità precedente
 *
 *********************************************************************/

BlockAST::BlockAST(std::vector<InitAST *> Def, std::vector<StmtAST *> Stmts) : Def(std::move(Def)), Stmts(std::move(Stmts)){};

BlockAST::BlockAST(std::vector<StmtAST *> Stmts) : Stmts(std::move(Stmts)){};

Value *BlockAST::codegen(driver &drv)
{
  // vettore per il salvataggio della symbol table
  std::vector<AllocaInst *> tmp;
  for (int i = 0; i < Def.size(); i++)
  {
    AllocaInst *boundval = (AllocaInst *)Def[i]->codegen(drv);
    if (!boundval)
      return nullptr;
    //* salvo il vecchio valore della varaiabile oscurata
    tmp.push_back(drv.NamedValues[Def[i]->getName()]);
    drv.NamedValues[Def[i]->getName()] = boundval;
  }
  Value *blockvalue;

  //* gestione di statement multipli
  for (int i = 0; i < Stmts.size(); i++)
  {
    blockvalue = Stmts[i]->codegen(drv);
    if (!blockvalue)
      return nullptr;
  }

  for (int i = 0; i < Def.size(); i++)
    //* ripristino il valore di tutte le vecchie variabili
    drv.NamedValues[Def[i]->getName()] = tmp[i];
  return blockvalue;
};

/*******************************************************************\
 * InitAST - Classe base per le definizioni di variabili
 * Fornisce struttura comune a diversi tipi di inizializzazioni, in particolare
 * per quelle di Binding e Assignment
 * Inizializza initType a INIT
 *********************************************************************/
std::string &InitAST::getName() { return Name; };
initType InitAST::getType() { return INIT; };

/************************* VarBindingAST: InitAST *************************/
VarBindingsAST::VarBindingsAST(std::string Name, ExprAST *Val) : Name(Name), Val(Val){};
std::string &VarBindingsAST::getName() { return Name; }; //* getName è un metodo definito in InitAST
initType VarBindingsAST::getType() { return BINDING; };  //* BINDING è un enum definito in driver.hpp

AllocaInst *VarBindingsAST::codegen(driver &drv)
{
  Function *fun = builder->GetInsertBlock()->getParent();
  Value *boundval;
  //* Val è definita
  if (Val)
    boundval = Val->codegen(drv);
  else
  {
    //* Inizializzazione default a 0.0 se Val è nullptr
    NumberExprAST *defaultVal = new NumberExprAST(0.0);
    boundval = defaultVal->codegen(drv);
  }
  //* Creo la variabile con il suo nome
  AllocaInst *Alloca = CreateEntryBlockAlloca(fun, Name);
  builder->CreateStore(boundval, Alloca);
  return Alloca;
};

/*******************************************************************\
 * ArrayBindingAST
 * Classe responsabile della creazione e inizializzazione di un array
 *
 * CreateStore -> Salva il valore in memoria in una specifica locazione di
 *                memoria specificata da CreateInBoundsGEP
 *
 *********************************************************************/

ArrayBindingAST::ArrayBindingAST(std::string Name, double Size, std::vector<ExprAST *> Val) : Name(Name), Size(Size), Val(std::move(Val)){};

std::string &ArrayBindingAST::getName() { return Name; };
initType ArrayBindingAST::getType() { return BINDING; };

AllocaInst *ArrayBindingAST::codegen(driver &drv)
{
  //* recupero riferimento alla funzione
  Function *fun = builder->GetInsertBlock()->getParent();
  int intSize = Size;

  //* crea tipo di array double con dimensione 'Size'
  ArrayType *AT = ArrayType::get(Type::getDoubleTy(*context), intSize);
  //* alloca memoria per l'array nell'entry point della funzione
  AllocaInst *Alloca = CreateEntryBlockAlloca(fun, Name, AT);
  //* Alloca è la variabile allocata che ora rappresenta l'array

  for (int i = 0; i < Size; i++)
  {
    //* calcola indirizzo i-esimo dell'array
    Value *Index = builder->CreateInBoundsGEP(AT, Alloca, ConstantInt::get(*context, APInt(32, i, true)));
    if (Val.size() != 0)
    {
      Value *arrayVal = Val[i]->codegen(drv);
      if (!arrayVal)
        return nullptr;
      builder->CreateStore(arrayVal, Index);
    }
  }
  return Alloca;
}

/*******************************************************************\
 * AssignmentExprAST
 * Rappresenta l'assegnamento di un valore a una variabile
 *
 * Pos mi rappresenta un esperessione che rappresenta l'indice dell'array
 *
 *
 *
 *********************************************************************/

AssignmentExprAST::AssignmentExprAST(std::string Name, ExprAST *Val, ExprAST *Pos) : Name(Name), Val(Val), Pos(Pos){};
std::string &AssignmentExprAST::getName() { return Name; };
initType AssignmentExprAST::getType() { return ASSIGNMENT; };

Value *AssignmentExprAST::codegen(driver &drv)
{
  AllocaInst *Variable = drv.NamedValues[Name];
  Value *boundval = Val->codegen(drv); // Genera il codice per il valore da assegnare.
  if (!boundval)
    return nullptr;
  //* controllo globale nel caso non sia stata trovata nell'ambiente locale
  if (!Variable)
  {
    GlobalVariable *globVar = module->getNamedGlobal(Name);
    if (!globVar)
      return nullptr;
    //* logica array globale
    if (Pos)
    {
      Value *doubleIndex = Pos->codegen(drv);
      if (!doubleIndex)
        return nullptr;
      //* trasformazione indice in Int
      Value *floatIndex = builder->CreateFPTrunc(doubleIndex, Type::getFloatTy(*context));
      Value *intIndex = builder->CreateFPToSI(floatIndex, Type::getInt32Ty(*context));
      //* calcola indirizzo dell'elemento dell'array all'indice specificato
      Value *cell = builder->CreateInBoundsGEP(globVar->getValueType(), globVar, intIndex);
      builder->CreateStore(boundval, cell);
    }
    //* caso in cui non si tratti di un array
    else
      builder->CreateStore(boundval, globVar);
    return boundval;
  }
  //* logica array locale
  if (Pos)
  {
    //* Variable = Array type
    Value *doubleIndex = Pos->codegen(drv);
    if (!doubleIndex)
      return nullptr;

    Value *floatIndex = builder->CreateFPTrunc(doubleIndex, Type::getFloatTy(*context));
    Value *intIndex = builder->CreateFPToSI(floatIndex, Type::getInt32Ty(*context));

    //* GetElementPointer -> calcola l'indirizzo dell'elemento dell'array all'indice specificato
    Value *cell = builder->CreateInBoundsGEP(Variable->getAllocatedType(), Variable, intIndex);
    builder->CreateStore(boundval, cell);
  }

  //* logica se variabile locale
  else
    //* Assegnamento effettivo salvando il valore in memoria
    builder->CreateStore(boundval, Variable);
  return boundval;
};

/*******************************************************************\
 * GlobalVariableAST
 * Rappresenta la dichiarazione di una variabile globale
 *
 *********************************************************************/

GlobalVariableAST::GlobalVariableAST(std::string Name, double Size, bool isArray) : Name(Name), Size(Size), isArray(isArray) {}
std::string &GlobalVariableAST::getName() { return Name; };
Value *GlobalVariableAST::codegen(driver &drv)
{
  GlobalVariable *globalVar;
  //* controllo se si tratta di un array
  if (isArray)
  {
    if (Size < 1)
      return nullptr;
    ArrayType *AT = ArrayType::get(Type::getDoubleTy(*context), Size);
    globalVar = new GlobalVariable(*module, AT, false, GlobalValue::CommonLinkage, ConstantFP::getNullValue(AT), Name);
  }
  else
  {
    //* creazione di una variabile globale llvm come singolo double
    globalVar = new GlobalVariable(*module, Type::getDoubleTy(*context), false, GlobalValue::CommonLinkage, ConstantFP::getNullValue(Type::getDoubleTy(*context)), Name);
  }
  //* stampa per debug
  globalVar->print(errs());
  fprintf(stderr, "\n");
  return globalVar;
}

/*******************************************************************\
 * IfStmtAST - Rappresenta un blocco IF
 *
 *
 *********************************************************************/
IfStmtAST::IfStmtAST(ExprAST *cond, StmtAST *trueblock, StmtAST *falseblock) : cond(cond), trueblock(trueblock), falseblock(falseblock){};

IfStmtAST::IfStmtAST(ExprAST *cond, StmtAST *trueblock) : cond(cond), trueblock(trueblock){};

Value *IfStmtAST::codegen(driver &drv)
{
  //* generazione del codice per la condizione dell'istruzione IF
  Value *CondV = cond->codegen(drv);
  if (!CondV)
    return nullptr;

  //* recupero la funzione corrente in cui è contenuto l'IF
  Function *fun = builder->GetInsertBlock()->getParent();
  BasicBlock *TrueBB = BasicBlock::Create(*context, "trueblock", fun);
  BasicBlock *FalseBB = BasicBlock::Create(*context, "falseblock");
  BasicBlock *MergeBB = BasicBlock::Create(*context, "mergeblock");

  //* Crea un'istruzione di branch condizionale che dirige il flusso di controllo (controllato da CondV)
  builder->CreateCondBr(CondV, TrueBB, FalseBB);

  //* imposta punto di inserimento del codice nel blocco true
  builder->SetInsertPoint(TrueBB);
  //* generazione del codice per il caso True
  Value *trueV = trueblock->codegen(drv);
  if (!trueV)
    return nullptr;

  //* assegno a TrueBB il blocco appena creato
  TrueBB = builder->GetInsertBlock();
  builder->CreateBr(MergeBB); //* crea salto incondizionato al blocco di merge

  builder->SetInsertPoint(FalseBB);
  Value *falseV;
  //* Inserimento del blocco nella funzione (non inserita dall'inizializzazione)
  fun->insert(fun->end(), FalseBB);
  builder->SetInsertPoint(FalseBB);
  if (falseblock)
  {
    falseV = falseblock->codegen(drv);
    if (!falseV)
      return nullptr;
    FalseBB = builder->GetInsertBlock();
  }
  builder->CreateBr(MergeBB);

  fun->insert(fun->end(), MergeBB);
  builder->SetInsertPoint(MergeBB);

  //* Phi node per la gestione dei valori provenienti da blocchi differenti (messi in mergeBB)
  PHINode *P = builder->CreatePHI(Type::getDoubleTy(*context), 2);
  P->addIncoming(ConstantFP::getNullValue(Type::getDoubleTy(*context)), TrueBB);
  P->addIncoming(ConstantFP::getNullValue(Type::getDoubleTy(*context)), FalseBB);
  return P;
};

/*******************************************************************
 * FOR BLOCK - Rappresenta un blocco FOR
 *
 ********************************************************************/
ForStmtAST::ForStmtAST(InitAST *init, ExprAST *cond, AssignmentExprAST *step, StmtAST *body) : init(init), cond(cond), step(step), body(body){};
Value *ForStmtAST::codegen(driver &drv)
{

  //* bool binding = false;
  //* recupero riferimento alla funzione -> entry point
  Function *fun = builder->GetInsertBlock()->getParent();
  //* inizializzazione BB
  BasicBlock *InitBB = BasicBlock::Create(*context, "init", fun);
  builder->CreateBr(InitBB);
  BasicBlock *CondBB = BasicBlock::Create(*context, "cond", fun);
  BasicBlock *LoopBB = BasicBlock::Create(*context, "loop", fun);
  BasicBlock *EndLoop = BasicBlock::Create(*context, "endloop", fun);

  builder->SetInsertPoint(InitBB);

  std::string varName = init->getName();
  AllocaInst *oldVar;
  Value *initVal = init->codegen(drv);
  if (!initVal)
    return nullptr;
  // controllo se init è binding - se si devo salvare il valore precedente e ripristinarlo alla fine del blocco
  if (init->getType() == BINDING)
  {
    oldVar = drv.NamedValues[varName];
    drv.NamedValues[varName] = (AllocaInst *)initVal;
    //* binding = true;
  }

  builder->CreateBr(CondBB);
  // cond
  builder->SetInsertPoint(CondBB);
  Value *condVal = cond->codegen(drv);
  if (!condVal)
    return nullptr;
  builder->CreateCondBr(condVal, LoopBB, EndLoop);
  // body
  builder->SetInsertPoint(LoopBB);
  Value *bodyVal = body->codegen(drv);
  if (!bodyVal)
    return nullptr;
  // step
  Value *stepVal = step->codegen(drv);
  if (!stepVal)
    return nullptr;

  // br incondizionato all'inizio del loop dallo step
  builder->CreateBr(CondBB);
  // End loop
  builder->SetInsertPoint(EndLoop);
  // Phi node per il valore di ritorno
  PHINode *P = builder->CreatePHI(Type::getDoubleTy(*context), 1);
  P->addIncoming(ConstantFP::getNullValue(Type::getDoubleTy(*context)), CondBB);

  //* Se BINDING ripristino la symbol table per mantere corretto lo scope
  if (init->getType() == BINDING)
  {
    //* if (binding){entro qui}
    drv.NamedValues[varName] = oldVar; // rimetto i valori originali della symb
  }
  return P;
};

/************************* Prototype Tree *************************/
PrototypeAST::PrototypeAST(std::string Name, std::vector<std::string> Args) : Name(Name), Args(std::move(Args)), emitcode(true){}; // Di regola il codice viene emesso

lexval PrototypeAST::getLexVal() const
{
  lexval lval = Name;
  return lval;
};

const std::vector<std::string> &PrototypeAST::getArgs() const
{
  return Args;
};

// Previene la doppia emissione del codice. Si veda il commento più avanti.
void PrototypeAST::noemit()
{
  emitcode = false;
};

Function *PrototypeAST::codegen(driver &drv)
{
  // Costruisce una struttura, qui chiamata FT, che rappresenta il "tipo" di una
  // funzione. Con ciò si intende a sua volta una coppia composta dal tipo
  // del risultato (valore di ritorno) e da un vettore che contiene il tipo di tutti
  // i parametri. Si ricordi, tuttavia, che nel nostro caso l'unico tipo è double.

  // Prima definiamo il vettore (qui chiamato Doubles) con il tipo degli argomenti
  std::vector<Type *> Doubles(Args.size(), Type::getDoubleTy(*context));
  // Quindi definiamo il tipo (FT) della funzione
  FunctionType *FT = FunctionType::get(Type::getDoubleTy(*context), Doubles, false);
  // Infine definiamo una funzione (al momento senza body) del tipo creato e con il nome
  // presente nel nodo AST. ExternalLinkage vuol dire che la funzione può avere
  // visibilità anche al di fuori del modulo
  Function *F = Function::Create(FT, Function::ExternalLinkage, Name, *module);

  // Ad ogni parametro della funzione F (che, è bene ricordare, è la rappresentazione
  // llvm di una funzione, non è una funzione C++) attribuiamo ora il nome specificato dal
  // programmatore e presente nel nodo AST relativo al prototipo
  unsigned Idx = 0;
  for (auto &Arg : F->args())
    Arg.setName(Args[Idx++]);

  /* Abbiamo completato la creazione del codice del prototipo.
     Il codice può quindi essere emesso, ma solo se esso corrisponde
     ad una dichiarazione extern. Se invece il prototipo fa parte
     della definizione "completa" di una funzione (prototipo+body) allora
     l'emissione viene fatta al momendo dell'emissione della funzione.
     In caso contrario nel codice si avrebbe sia una dichiarazione
     (come nel caso di funzione esterna) sia una definizione della stessa
     funzione.
  */
  if (emitcode)
  {
    F->print(errs());
    fprintf(stderr, "\n");
  };

  return F;
}

/************************* Function Tree **************************/
FunctionAST::FunctionAST(PrototypeAST *Proto, ExprAST *Body) : Proto(Proto), Body(Body){};

Function *FunctionAST::codegen(driver &drv)
{
  // Verifica che la funzione non sia già presente nel modulo, cioò che non
  // si tenti una "doppia definizion"
  Function *function =
      module->getFunction(std::get<std::string>(Proto->getLexVal()));
  // Se la funzione non è già presente, si prova a definirla, innanzitutto
  // generando (ma non emettendo) il codice del prototipo
  if (!function)
    function = Proto->codegen(drv);
  else
    return nullptr;
  // Se, per qualche ragione, la definizione "fallisce" si restituisce nullptr
  if (!function)
    return nullptr;

  // Altrimenti si crea un blocco di base in cui iniziare a inserire il codice
  BasicBlock *BB = BasicBlock::Create(*context, "entry", function);
  builder->SetInsertPoint(BB);

  // Ora viene la parte "più delicata". Per ogni parametro formale della
  // funzione, nella symbol table si registra una coppia in cui la chiave
  // è il nome del parametro mentre il valore è un'istruzione alloca, generata
  // invocando l'utility CreateEntryBlockAlloca già commentata.
  // Vale comunque la pena ricordare: l'istruzione di allocazione riserva
  // spazio in memoria (nel nostro caso per un double) e scrive l'indirizzo
  // in un registro SSA
  // Il builder crea poi un'istruzione che memorizza il valore del parametro x
  // (al momento contenuto nel registro SSA %x) nell'area di memoria allocata.
  // Si noti che il builder conosce il registro che contiene il puntatore all'area
  // perché esso è parte della rappresentazione C++ dell'istruzione di allocazione
  // (variabile Alloca)

  for (auto &Arg : function->args())
  {
    // Genera l'istruzione di allocazione per il parametro corrente
    AllocaInst *Alloca = CreateEntryBlockAlloca(function, Arg.getName());
    // Genera un'istruzione per la memorizzazione del parametro nell'area
    // di memoria allocata
    builder->CreateStore(&Arg, Alloca);
    // Registra gli argomenti nella symbol table per eventuale riferimento futuro
    drv.NamedValues[std::string(Arg.getName())] = Alloca;
  }

  // Ora può essere generato il codice corssipondente al body (che potrà
  // fare riferimento alla symbol table)
  if (Value *RetVal = Body->codegen(drv))
  {
    // Se la generazione termina senza errori, ciò che rimane da fare è
    // di generare l'istruzione return, che ("a tempo di esecuzione") prenderà
    // il valore lasciato nel registro RetVal
    builder->CreateRet(RetVal);

    // Effettua la validazione del codice e un controllo di consistenza
    verifyFunction(*function);

    // Emissione del codice su su stderr)
    function->print(errs());
    fprintf(stderr, "\n");
    return function;
  }

  // Errore nella definizione. La funzione viene rimossa
  function->eraseFromParent();
  return nullptr;
};