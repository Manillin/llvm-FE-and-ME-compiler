# Spiegazione Progetto FrontEnd Kaleidoscope

Nel seguente file viene spiegato per intero il progetto di creazione di un FE per Kaleidoscope.  
> Placeholder per una table of contents (...)


# File sorgenti:

## Parser.yy

File che serve per generare un parser sintattico con l'aiuto `Bison`, che trasforma le specifiche grammaticali in un programma C++ `parser.cpp` che analizza token secondo le specifiche definite.   
Il file è diviso in diverse sezioni, verrà mostrata una panoramica di queste:  

- **Direttive e Dichiarazioni iniziali:**  
Questa sezione include direttive per bison e dichiaraazioni iniziali 

- **Codice richiesto:**  
Sezione che contiene codice C++ da includere a inizio del file che Bison andrà a generare.  

- **Contesto di parsing:**  
Definisce i parametri passati al parser, nel nostro caso un oggetto `driver`
    ```
    %param {driver& drv}
    ```

- **Regole di Parsing:**  
Sezione più importante del file, qui viene definita la **grammatica** del linguaggio tramite regole di riscrittura (produzioni). Ogni regola associa a un non temrinale una sequenza del vocabolario della grammatica, specificando anche cosa fare quando quella sequenza viene riconosciuta.  
    ```
    assignment: 
    "id" "=" exp    {$$ = new AssignmentExprAST($1,$3);}
    ```

    Questa regola di esempio definisce come vinee gestita un'assegnazione: se il parser riconosce un identificatore seguito da un uguale e un espressione $\rightarrow$ crea un nuovo oggetto `AssignmentExprAST`.  

- **Codice Utente:**  
Segna la fine delle regole di parsing e l'inizio del codice utente arbitrario, non verrà modificata questa sezione nel nostro progetto.  


### Gestione delle precedenze nelle produzioni   

La grammatica definita da Bison ha prefissi in comune che possono creare ambiguità e serve un modo per creare precedenze all'interno delle produzioni per evitare ricorsioni infinite o un incorretto parsing.  
Le precedenze vengono gestite nel seguente modo:  
- Dichiarazioni %left, %right, %nonassoc:  
    Queste dichiarazioni specificano l'associatività degi operatori e le regole di precedenza

    1. `%left`:  
    Attribuisce precedenza associativa a sinistra agli operatori a cui viene applicata tale regola  
    2. `%right`:  
    Precedenza associativa a destra

    3. `%prec`:  
    Viene utilizzata per assegnare una precedenza esplicita (manualmente) a una produzione, utile per gestire casi speciali come l'operatore ternario o per ambiguità specifiche:   
    nell'istruzione `ifstmt` viene usato `%prec "then" ` per assicurare che la produzione abbia la precedenza corretta in relazione agli operatori `then` ed `else` garantendo che le istruzioni condizionali siano analizzate correttamnte in presenza di costrutti `if-else`.  




<br> <br>


### Differenza tra `Binding` e `Assignment`:

Il `Binding` si riferisce al processo di **dichiarazione** e **inizializzazione** di una variabile.  Durante il binding viene riservata una porzione di memoria (registo o locazione in mem) e viene associata a un nome (*la variabile*).  


L' `Assignment` si riferisce al processo di assegnare un **nuovo** valore a una variabile precedentemenete dichiarata ed inizializzata (quindi con binding già effettuato).  
L'assegnamento aggiorna semplicemente il valore memorizzato nella locazione di memoria associata alla variabile.  


# Istruzioni e Metodi notevoli LLVM


<br>

`NamedValues` $\rightarrow$ Consiste in una HashMap che associa al nome di ogni variabile una rappresentazione di memoria.  
Nel contesto llvm una variabile può essere rappresentata da un'istruzione di allocazione (`AllocaInst` $\rightarrow$ alloca memoria sullo stack e restituisce un ptr a quella porzione di memoria, tale ptr viene utilizzato per leggere o scrivere il valore della variabile).  
<br>

--- 

<br>

`codegen` $\rightarrow$ È il metodo di classe responsabile della generazione di codice IR.   
ES (creazione variabile):  si ha la funzione `f(x)`
1. Cerca la rappresentazione della variabile `x` in `NamedValues` usando il nome della variabile come Key $\rightarrow$ `{ 'x': <allocazione_x> }`  
2.  Se la variabile non è definita (non esiste in NamedValues) si genera un errore
3. Se la variabile è definita allora si genera un'istruzione di `load` che legge il valore dalla memoria allocata per la variabile e lo restituisce.  


<br>


--- 

<br>

```c++
LLVMContext *context = new LLVMContext;
Module *module = new Module("Kaleidoscope", *context);
IRBuilder<> *builder = new IRBuilder(*context);
driver::driver(): trace_parcing(false), trace_scanning(false) {};


```

1. `LLVMContext *context = new LLVMContext;`  
Crea un nuovo `LLVMContext`, che è un contenitore per tutti i dati globali usati durante la generazione del codice LLVM. Serve per mantenere le versioni dei tipi e altre informazioni importanti durante la compilazione.

2. `Module *module = new Module('Keleidoscope', *context)`  
Crea un nuovo `Module` che rappresenta l'unità di compilazione di codice LLVM  
`Module` $\rightarrow$ rappresenta l'unità di compilazione principale del codice LLVM. È qui che tutte le **funzioni, variabili globali e definizioni di tipo** vengono raccolte e organizzate. Il modulo serve come contenitore per tutto il codice che sarà compilato o eseguito.  

3. `IRBuilder <> *builder = new IRBuilder(*context)`  
Crea un nuovo IRBuilder, che è uno strumento (helper) per costruire facilmente istruzioni LLVM IR (Intermediate Representation). L'IRBuilder semplifica la generazione di codice LLVM offrendo un'interfaccia per inserire istruzioni e definire strutture di controllo come cicli e condizioni.


4. `driver::driver(): trace_parcing(false), trace_scanning(false) {};`   
Classe `driver` che è la classe principale per gestire il proceso di compilazione.  Imposta i flag iniziali per il tracing del parsing e scanning, per tracciare e modellare il comportamento del compialatore.  


<br>





---


<br>

### Ampliare la grammatica:

1. Aggiungere nuovi token nel lexer
2. Aggiungere i nuovi token  nel parser
3. Creare le nuove regole grammaticali nel parser
4. Creare e implementare le corrispettive ASTclasses in driver.cpp



<br>


--- 


<br>

## Cose capite bene

1. AssignmentExprAST
2. InitAST (che eredita da RootAST) e initType (enum)
3. VarBindingAST (da riguardare e commentare)
4. IfStmtAST
