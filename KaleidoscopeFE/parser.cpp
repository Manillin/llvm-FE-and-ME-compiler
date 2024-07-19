// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hpp"


// Unqualified %code blocks.
#line 40 "parser.yy"

# include "driver.hpp"

#line 50 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 142 "parser.cpp"

  /// Build a parser object.
  parser::parser (driver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_assignment: // assignment
        value.YY_MOVE_OR_COPY< AssignmentExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< BlockAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_initexp: // initexp
      case symbol_kind::S_expif: // expif
      case symbol_kind::S_condexp: // condexp
      case symbol_kind::S_relexp: // relexp
      case symbol_kind::S_idexp: // idexp
        value.YY_MOVE_OR_COPY< ExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forstmt: // forstmt
        value.YY_MOVE_OR_COPY< ForStmtAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.YY_MOVE_OR_COPY< FunctionAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_globalvar: // globalvar
        value.YY_MOVE_OR_COPY< GlobalVariableAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ifstmt: // ifstmt
        value.YY_MOVE_OR_COPY< IfStmtAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_binding: // binding
      case symbol_kind::S_init: // init
        value.YY_MOVE_OR_COPY< InitAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        value.YY_MOVE_OR_COPY< PrototypeAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        value.YY_MOVE_OR_COPY< RootAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.YY_MOVE_OR_COPY< StmtAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.YY_MOVE_OR_COPY< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vardefs: // vardefs
        value.YY_MOVE_OR_COPY< std::vector<InitAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
        value.YY_MOVE_OR_COPY< std::vector<StmtAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_idseq: // idseq
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_assignment: // assignment
        value.move< AssignmentExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< BlockAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_initexp: // initexp
      case symbol_kind::S_expif: // expif
      case symbol_kind::S_condexp: // condexp
      case symbol_kind::S_relexp: // relexp
      case symbol_kind::S_idexp: // idexp
        value.move< ExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forstmt: // forstmt
        value.move< ForStmtAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.move< FunctionAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_globalvar: // globalvar
        value.move< GlobalVariableAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ifstmt: // ifstmt
        value.move< IfStmtAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_binding: // binding
      case symbol_kind::S_init: // init
        value.move< InitAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        value.move< PrototypeAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        value.move< RootAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< StmtAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.move< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vardefs: // vardefs
        value.move< std::vector<InitAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
        value.move< std::vector<StmtAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_idseq: // idseq
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_assignment: // assignment
        value.copy< AssignmentExprAST* > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.copy< BlockAST* > (that.value);
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_initexp: // initexp
      case symbol_kind::S_expif: // expif
      case symbol_kind::S_condexp: // condexp
      case symbol_kind::S_relexp: // relexp
      case symbol_kind::S_idexp: // idexp
        value.copy< ExprAST* > (that.value);
        break;

      case symbol_kind::S_forstmt: // forstmt
        value.copy< ForStmtAST* > (that.value);
        break;

      case symbol_kind::S_definition: // definition
        value.copy< FunctionAST* > (that.value);
        break;

      case symbol_kind::S_globalvar: // globalvar
        value.copy< GlobalVariableAST* > (that.value);
        break;

      case symbol_kind::S_ifstmt: // ifstmt
        value.copy< IfStmtAST* > (that.value);
        break;

      case symbol_kind::S_binding: // binding
      case symbol_kind::S_init: // init
        value.copy< InitAST* > (that.value);
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        value.copy< PrototypeAST* > (that.value);
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        value.copy< RootAST* > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.copy< StmtAST* > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.copy< std::vector<ExprAST*> > (that.value);
        break;

      case symbol_kind::S_vardefs: // vardefs
        value.copy< std::vector<InitAST*> > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
        value.copy< std::vector<StmtAST*> > (that.value);
        break;

      case symbol_kind::S_idseq: // idseq
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_assignment: // assignment
        value.move< AssignmentExprAST* > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.move< BlockAST* > (that.value);
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_initexp: // initexp
      case symbol_kind::S_expif: // expif
      case symbol_kind::S_condexp: // condexp
      case symbol_kind::S_relexp: // relexp
      case symbol_kind::S_idexp: // idexp
        value.move< ExprAST* > (that.value);
        break;

      case symbol_kind::S_forstmt: // forstmt
        value.move< ForStmtAST* > (that.value);
        break;

      case symbol_kind::S_definition: // definition
        value.move< FunctionAST* > (that.value);
        break;

      case symbol_kind::S_globalvar: // globalvar
        value.move< GlobalVariableAST* > (that.value);
        break;

      case symbol_kind::S_ifstmt: // ifstmt
        value.move< IfStmtAST* > (that.value);
        break;

      case symbol_kind::S_binding: // binding
      case symbol_kind::S_init: // init
        value.move< InitAST* > (that.value);
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        value.move< PrototypeAST* > (that.value);
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        value.move< RootAST* > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< StmtAST* > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< double > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.move< std::vector<ExprAST*> > (that.value);
        break;

      case symbol_kind::S_vardefs: // vardefs
        value.move< std::vector<InitAST*> > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
        value.move< std::vector<StmtAST*> > (that.value);
        break;

      case symbol_kind::S_idseq: // idseq
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_assignment: // assignment
        yylhs.value.emplace< AssignmentExprAST* > ();
        break;

      case symbol_kind::S_block: // block
        yylhs.value.emplace< BlockAST* > ();
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_initexp: // initexp
      case symbol_kind::S_expif: // expif
      case symbol_kind::S_condexp: // condexp
      case symbol_kind::S_relexp: // relexp
      case symbol_kind::S_idexp: // idexp
        yylhs.value.emplace< ExprAST* > ();
        break;

      case symbol_kind::S_forstmt: // forstmt
        yylhs.value.emplace< ForStmtAST* > ();
        break;

      case symbol_kind::S_definition: // definition
        yylhs.value.emplace< FunctionAST* > ();
        break;

      case symbol_kind::S_globalvar: // globalvar
        yylhs.value.emplace< GlobalVariableAST* > ();
        break;

      case symbol_kind::S_ifstmt: // ifstmt
        yylhs.value.emplace< IfStmtAST* > ();
        break;

      case symbol_kind::S_binding: // binding
      case symbol_kind::S_init: // init
        yylhs.value.emplace< InitAST* > ();
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        yylhs.value.emplace< PrototypeAST* > ();
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        yylhs.value.emplace< RootAST* > ();
        break;

      case symbol_kind::S_stmt: // stmt
        yylhs.value.emplace< StmtAST* > ();
        break;

      case symbol_kind::S_NUMBER: // "number"
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_IDENTIFIER: // "id"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        yylhs.value.emplace< std::vector<ExprAST*> > ();
        break;

      case symbol_kind::S_vardefs: // vardefs
        yylhs.value.emplace< std::vector<InitAST*> > ();
        break;

      case symbol_kind::S_stmts: // stmts
        yylhs.value.emplace< std::vector<StmtAST*> > ();
        break;

      case symbol_kind::S_idseq: // idseq
        yylhs.value.emplace< std::vector<std::string> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // startsymb: program
#line 117 "parser.yy"
                        { drv.root = yystack_[0].value.as < RootAST* > (); }
#line 921 "parser.cpp"
    break;

  case 3: // program: %empty
#line 120 "parser.yy"
                        { yylhs.value.as < RootAST* > () = new SeqAST(nullptr,nullptr); }
#line 927 "parser.cpp"
    break;

  case 4: // program: top ";" program
#line 121 "parser.yy"
                        { yylhs.value.as < RootAST* > () = new SeqAST(yystack_[2].value.as < RootAST* > (),yystack_[0].value.as < RootAST* > ()); }
#line 933 "parser.cpp"
    break;

  case 5: // top: %empty
#line 124 "parser.yy"
                        { yylhs.value.as < RootAST* > () = nullptr; }
#line 939 "parser.cpp"
    break;

  case 6: // top: definition
#line 125 "parser.yy"
                        { yylhs.value.as < RootAST* > () = yystack_[0].value.as < FunctionAST* > (); }
#line 945 "parser.cpp"
    break;

  case 7: // top: external
#line 126 "parser.yy"
                        { yylhs.value.as < RootAST* > () = yystack_[0].value.as < PrototypeAST* > (); }
#line 951 "parser.cpp"
    break;

  case 8: // top: globalvar
#line 127 "parser.yy"
                        { yylhs.value.as < RootAST* > () = yystack_[0].value.as < GlobalVariableAST* > (); }
#line 957 "parser.cpp"
    break;

  case 9: // definition: "def" proto block
#line 132 "parser.yy"
                          { yylhs.value.as < FunctionAST* > () = new FunctionAST(yystack_[1].value.as < PrototypeAST* > (),yystack_[0].value.as < BlockAST* > ()); yystack_[1].value.as < PrototypeAST* > ()->noemit(); }
#line 963 "parser.cpp"
    break;

  case 10: // external: "extern" proto
#line 135 "parser.yy"
                        { yylhs.value.as < PrototypeAST* > () = yystack_[0].value.as < PrototypeAST* > (); }
#line 969 "parser.cpp"
    break;

  case 11: // proto: "id" "(" idseq ")"
#line 138 "parser.yy"
                        { yylhs.value.as < PrototypeAST* > () = new PrototypeAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < std::vector<std::string> > ());  }
#line 975 "parser.cpp"
    break;

  case 12: // globalvar: "global" "id"
#line 143 "parser.yy"
                                  { yylhs.value.as < GlobalVariableAST* > () = new GlobalVariableAST(yystack_[0].value.as < std::string > ()); }
#line 981 "parser.cpp"
    break;

  case 13: // globalvar: "global" "id" "[" "number" "]"
#line 144 "parser.yy"
                                  { yylhs.value.as < GlobalVariableAST* > () = new GlobalVariableAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < double > (),true); }
#line 987 "parser.cpp"
    break;

  case 14: // idseq: %empty
#line 148 "parser.yy"
                        { std::vector<std::string> args; yylhs.value.as < std::vector<std::string> > () = args; }
#line 993 "parser.cpp"
    break;

  case 15: // idseq: "id" idseq
#line 149 "parser.yy"
                        { yystack_[0].value.as < std::vector<std::string> > ().insert(yystack_[0].value.as < std::vector<std::string> > ().begin(),yystack_[1].value.as < std::string > ()); yylhs.value.as < std::vector<std::string> > () = yystack_[0].value.as < std::vector<std::string> > (); }
#line 999 "parser.cpp"
    break;

  case 16: // stmts: stmt
#line 152 "parser.yy"
                        {std::vector<StmtAST*> statemets; statemets.insert(statemets.begin(),yystack_[0].value.as < StmtAST* > ()); yylhs.value.as < std::vector<StmtAST*> > () = statemets; }
#line 1005 "parser.cpp"
    break;

  case 17: // stmts: stmt ";" stmts
#line 153 "parser.yy"
                        {yystack_[0].value.as < std::vector<StmtAST*> > ().insert(yystack_[0].value.as < std::vector<StmtAST*> > ().begin(),yystack_[2].value.as < StmtAST* > ()); yylhs.value.as < std::vector<StmtAST*> > () = yystack_[0].value.as < std::vector<StmtAST*> > ();}
#line 1011 "parser.cpp"
    break;

  case 18: // stmt: assignment
#line 156 "parser.yy"
                        {yylhs.value.as < StmtAST* > () = yystack_[0].value.as < AssignmentExprAST* > ();}
#line 1017 "parser.cpp"
    break;

  case 19: // stmt: block
#line 157 "parser.yy"
                        {yylhs.value.as < StmtAST* > () = yystack_[0].value.as < BlockAST* > ();}
#line 1023 "parser.cpp"
    break;

  case 20: // stmt: ifstmt
#line 158 "parser.yy"
                        {yylhs.value.as < StmtAST* > () = yystack_[0].value.as < IfStmtAST* > ();}
#line 1029 "parser.cpp"
    break;

  case 21: // stmt: forstmt
#line 159 "parser.yy"
                        {yylhs.value.as < StmtAST* > () = yystack_[0].value.as < ForStmtAST* > ();}
#line 1035 "parser.cpp"
    break;

  case 22: // stmt: exp
#line 160 "parser.yy"
                        {yylhs.value.as < StmtAST* > () = yystack_[0].value.as < ExprAST* > ();}
#line 1041 "parser.cpp"
    break;

  case 23: // assignment: "id" "=" exp
#line 163 "parser.yy"
                            {yylhs.value.as < AssignmentExprAST* > () = new AssignmentExprAST(yystack_[2].value.as < std::string > (),yystack_[0].value.as < ExprAST* > ());}
#line 1047 "parser.cpp"
    break;

  case 24: // assignment: "++" "id"
#line 164 "parser.yy"
                            {yylhs.value.as < AssignmentExprAST* > () = new AssignmentExprAST(yystack_[0].value.as < std::string > (), new BinaryExprAST('+',new VariableExprAST(yystack_[0].value.as < std::string > ()),new NumberExprAST(1)));}
#line 1053 "parser.cpp"
    break;

  case 25: // assignment: "id" "++"
#line 165 "parser.yy"
                            {yylhs.value.as < AssignmentExprAST* > () = new AssignmentExprAST(yystack_[1].value.as < std::string > (), new BinaryExprAST('+',new VariableExprAST(yystack_[1].value.as < std::string > ()),new NumberExprAST(1)));}
#line 1059 "parser.cpp"
    break;

  case 26: // assignment: "--" "id"
#line 166 "parser.yy"
                            {yylhs.value.as < AssignmentExprAST* > () = new AssignmentExprAST(yystack_[0].value.as < std::string > (), new BinaryExprAST('-',new VariableExprAST(yystack_[0].value.as < std::string > ()),new NumberExprAST(1)));}
#line 1065 "parser.cpp"
    break;

  case 27: // assignment: "id" "--"
#line 167 "parser.yy"
                            {yylhs.value.as < AssignmentExprAST* > () = new AssignmentExprAST(yystack_[1].value.as < std::string > (), new BinaryExprAST('-',new VariableExprAST(yystack_[1].value.as < std::string > ()),new NumberExprAST(1)));}
#line 1071 "parser.cpp"
    break;

  case 28: // assignment: "id" "[" exp "]" "=" exp
#line 168 "parser.yy"
                            {yylhs.value.as < AssignmentExprAST* > () = new AssignmentExprAST(yystack_[5].value.as < std::string > (),yystack_[0].value.as < ExprAST* > (),yystack_[3].value.as < ExprAST* > ()); }
#line 1077 "parser.cpp"
    break;

  case 29: // block: "{" stmts "}"
#line 172 "parser.yy"
                            { yylhs.value.as < BlockAST* > () = new BlockAST(yystack_[1].value.as < std::vector<StmtAST*> > ()); }
#line 1083 "parser.cpp"
    break;

  case 30: // block: "{" vardefs ";" stmts "}"
#line 173 "parser.yy"
                            { yylhs.value.as < BlockAST* > () = new BlockAST(yystack_[3].value.as < std::vector<InitAST*> > (),yystack_[1].value.as < std::vector<StmtAST*> > ()); }
#line 1089 "parser.cpp"
    break;

  case 31: // exp: "-" exp
#line 185 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('-',new NumberExprAST(0),yystack_[0].value.as < ExprAST* > ());}
#line 1095 "parser.cpp"
    break;

  case 32: // exp: exp "+" exp
#line 186 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('+',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1101 "parser.cpp"
    break;

  case 33: // exp: exp "-" exp
#line 187 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('-',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1107 "parser.cpp"
    break;

  case 34: // exp: exp "*" exp
#line 188 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('*',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1113 "parser.cpp"
    break;

  case 35: // exp: exp "/" exp
#line 189 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('/',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1119 "parser.cpp"
    break;

  case 36: // exp: idexp
#line 190 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1125 "parser.cpp"
    break;

  case 37: // exp: "(" exp ")"
#line 191 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = yystack_[1].value.as < ExprAST* > (); }
#line 1131 "parser.cpp"
    break;

  case 38: // exp: "number"
#line 192 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new NumberExprAST(yystack_[0].value.as < double > ()); }
#line 1137 "parser.cpp"
    break;

  case 39: // exp: expif
#line 193 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1143 "parser.cpp"
    break;

  case 40: // vardefs: binding
#line 197 "parser.yy"
                        { std::vector<InitAST*> definitions; definitions.push_back(yystack_[0].value.as < InitAST* > ()); yylhs.value.as < std::vector<InitAST*> > () = definitions; }
#line 1149 "parser.cpp"
    break;

  case 41: // vardefs: vardefs ";" binding
#line 198 "parser.yy"
                        { yystack_[2].value.as < std::vector<InitAST*> > ().push_back(yystack_[0].value.as < InitAST* > ()); yylhs.value.as < std::vector<InitAST*> > () = yystack_[2].value.as < std::vector<InitAST*> > (); }
#line 1155 "parser.cpp"
    break;

  case 42: // binding: "var" "id" initexp
#line 201 "parser.yy"
                                                    { yylhs.value.as < InitAST* > () = new VarBindingsAST(yystack_[1].value.as < std::string > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1161 "parser.cpp"
    break;

  case 43: // binding: "var" "id" "[" "number" "]"
#line 202 "parser.yy"
                                                    { yylhs.value.as < InitAST* > () = new ArrayBindingAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < double > ());}
#line 1167 "parser.cpp"
    break;

  case 44: // binding: "var" "id" "[" "number" "]" "=" "{" explist "}"
#line 203 "parser.yy"
                                                    { yylhs.value.as < InitAST* > () = new ArrayBindingAST(yystack_[7].value.as < std::string > (),yystack_[5].value.as < double > (),yystack_[1].value.as < std::vector<ExprAST*> > ());}
#line 1173 "parser.cpp"
    break;

  case 45: // initexp: %empty
#line 206 "parser.yy"
          {yylhs.value.as < ExprAST* > () = nullptr;}
#line 1179 "parser.cpp"
    break;

  case 46: // initexp: "=" exp
#line 207 "parser.yy"
          {yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > ();}
#line 1185 "parser.cpp"
    break;

  case 47: // expif: condexp "?" exp ":" exp
#line 210 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new IfExprAST(yystack_[4].value.as < ExprAST* > (),yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ());}
#line 1191 "parser.cpp"
    break;

  case 48: // ifstmt: "if" "(" condexp ")" stmt
#line 216 "parser.yy"
                                              {yylhs.value.as < IfStmtAST* > () = new IfStmtAST(yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < StmtAST* > ()); }
#line 1197 "parser.cpp"
    break;

  case 49: // ifstmt: "if" "(" condexp ")" stmt "else" stmt
#line 217 "parser.yy"
                                              {yylhs.value.as < IfStmtAST* > () = new IfStmtAST(yystack_[4].value.as < ExprAST* > (),yystack_[2].value.as < StmtAST* > (),yystack_[0].value.as < StmtAST* > ()); }
#line 1203 "parser.cpp"
    break;

  case 50: // forstmt: "for" "(" init ";" condexp ";" assignment ")" stmt
#line 220 "parser.yy"
                                                   {yylhs.value.as < ForStmtAST* > () = new ForStmtAST(yystack_[6].value.as < InitAST* > (),yystack_[4].value.as < ExprAST* > (),yystack_[2].value.as < AssignmentExprAST* > (),yystack_[0].value.as < StmtAST* > ());}
#line 1209 "parser.cpp"
    break;

  case 51: // init: binding
#line 223 "parser.yy"
          {yylhs.value.as < InitAST* > () = yystack_[0].value.as < InitAST* > ();}
#line 1215 "parser.cpp"
    break;

  case 52: // init: assignment
#line 224 "parser.yy"
             {yylhs.value.as < InitAST* > () = yystack_[0].value.as < AssignmentExprAST* > ();}
#line 1221 "parser.cpp"
    break;

  case 53: // condexp: relexp
#line 227 "parser.yy"
                         {yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > ();}
#line 1227 "parser.cpp"
    break;

  case 54: // condexp: relexp "and" condexp
#line 228 "parser.yy"
                         {yylhs.value.as < ExprAST* > () = new BinaryExprAST('a',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ());}
#line 1233 "parser.cpp"
    break;

  case 55: // condexp: relexp "or" condexp
#line 229 "parser.yy"
                         {yylhs.value.as < ExprAST* > () = new BinaryExprAST('o',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ());}
#line 1239 "parser.cpp"
    break;

  case 56: // condexp: "not" condexp
#line 230 "parser.yy"
                         {yylhs.value.as < ExprAST* > () = new BinaryExprAST('n',nullptr,yystack_[0].value.as < ExprAST* > ());}
#line 1245 "parser.cpp"
    break;

  case 57: // condexp: "(" condexp ")"
#line 231 "parser.yy"
                         {yylhs.value.as < ExprAST* > () = yystack_[1].value.as < ExprAST* > ();}
#line 1251 "parser.cpp"
    break;

  case 58: // relexp: exp "<" exp
#line 234 "parser.yy"
                         { yylhs.value.as < ExprAST* > () = new BinaryExprAST('<',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1257 "parser.cpp"
    break;

  case 59: // relexp: exp ">" exp
#line 235 "parser.yy"
                         { yylhs.value.as < ExprAST* > () = new BinaryExprAST('>',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1263 "parser.cpp"
    break;

  case 60: // relexp: exp "==" exp
#line 236 "parser.yy"
                         { yylhs.value.as < ExprAST* > () = new BinaryExprAST('=',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1269 "parser.cpp"
    break;

  case 61: // idexp: "id"
#line 239 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new VariableExprAST(yystack_[0].value.as < std::string > ()); }
#line 1275 "parser.cpp"
    break;

  case 62: // idexp: "id" "(" optexp ")"
#line 240 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new CallExprAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < std::vector<ExprAST*> > ()); }
#line 1281 "parser.cpp"
    break;

  case 63: // idexp: "id" "[" exp "]"
#line 241 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new VariableExprAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < ExprAST* > (),true);}
#line 1287 "parser.cpp"
    break;

  case 64: // optexp: %empty
#line 244 "parser.yy"
                        { std::vector<ExprAST*> args;
			 yylhs.value.as < std::vector<ExprAST*> > () = args; }
#line 1294 "parser.cpp"
    break;

  case 65: // optexp: explist
#line 246 "parser.yy"
                        { yylhs.value.as < std::vector<ExprAST*> > () = yystack_[0].value.as < std::vector<ExprAST*> > (); }
#line 1300 "parser.cpp"
    break;

  case 66: // explist: exp
#line 249 "parser.yy"
                        { std::vector<ExprAST*> args;
                          args.push_back(yystack_[0].value.as < ExprAST* > ());
			                    yylhs.value.as < std::vector<ExprAST*> > () = args;
                        }
#line 1309 "parser.cpp"
    break;

  case 67: // explist: exp "," explist
#line 253 "parser.yy"
                        { yystack_[0].value.as < std::vector<ExprAST*> > ().insert(yystack_[0].value.as < std::vector<ExprAST*> > ().begin(), yystack_[2].value.as < ExprAST* > ()); yylhs.value.as < std::vector<ExprAST*> > () = yystack_[0].value.as < std::vector<ExprAST*> > (); }
#line 1315 "parser.cpp"
    break;


#line 1319 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -100;

  const signed char parser::yytable_ninf_ = -6;

  const short
  parser::yypact_[] =
  {
      39,   -15,   -15,   -11,    25,  -100,    47,  -100,  -100,  -100,
      46,  -100,    42,    48,  -100,    39,    37,    70,  -100,    44,
    -100,    37,    68,    59,     2,    60,     2,     2,    66,    86,
      98,    12,  -100,    88,   109,  -100,  -100,   193,   111,  -100,
    -100,  -100,  -100,   105,    -8,  -100,    99,  -100,  -100,  -100,
      43,    75,  -100,   169,     8,   193,  -100,    55,     2,     0,
    -100,  -100,     2,     2,     2,  -100,   100,     2,     2,     2,
       2,     2,     2,     2,    70,     2,     2,     2,  -100,     2,
    -100,  -100,     2,    92,  -100,    74,    64,  -100,  -100,   117,
     157,   116,  -100,   193,   107,  -100,    75,    75,  -100,  -100,
     193,   193,   193,   114,  -100,   181,  -100,  -100,   129,   193,
     120,   100,     2,     2,     2,  -100,   113,  -100,     2,  -100,
     123,   112,   142,    11,  -100,     2,   193,   108,   100,   113,
      -1,   193,     2,  -100,   130,   125,   100,  -100,  -100
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,     0,     2,     0,     6,     7,     8,
       0,    10,     0,    12,     1,     3,    14,     0,     9,     0,
       4,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    38,     0,    16,    18,    19,    22,     0,    40,
      39,    20,    21,     0,    53,    36,     0,    15,    11,    26,
      61,    31,    24,     0,     0,     0,    56,    45,     0,     0,
      27,    25,    64,     0,     0,    29,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    13,     0,
      37,    57,     0,     0,    42,     0,     0,    52,    51,     0,
      66,     0,    65,    23,     0,    17,    33,    32,    34,    35,
      58,    59,    60,     0,    41,     0,    54,    55,     0,    46,
       0,     0,     0,     0,     0,    62,    63,    30,     0,    63,
      43,    48,     0,     0,    67,     0,    47,     0,     0,     0,
       0,    28,     0,    49,     0,     0,     0,    44,    50
  };

  const short
  parser::yypgoto_[] =
  {
    -100,  -100,   138,  -100,  -100,  -100,   152,  -100,   134,   -10,
     -99,   -58,   144,   -24,  -100,   -48,  -100,  -100,  -100,  -100,
    -100,   -17,  -100,  -100,  -100,   -53
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,     8,    11,     9,    22,    33,
      34,    35,    36,    37,    38,    39,    84,    40,    41,    42,
      89,    43,    44,    45,    91,    92
  };

  const short
  parser::yytable_[] =
  {
      51,    87,    53,    55,    23,    23,    25,    25,    24,    54,
      56,    88,   121,    26,   130,    76,    77,    60,    10,    61,
      81,    75,    13,    62,    75,    14,   104,    27,    28,   133,
      63,    64,    86,    86,    55,    50,    32,   138,    90,    93,
      94,    85,    -5,    96,    97,    98,    99,   100,   101,   102,
      15,   105,    55,    55,    62,   108,    95,    16,   109,   106,
     107,   124,    79,    17,   103,     1,     2,    19,     3,    60,
      21,    61,   134,    82,    83,    23,    24,    25,    46,   135,
      48,    26,    63,   112,    69,    70,   111,    75,   122,    55,
      90,    17,    49,    52,   126,    27,   123,    58,    28,    57,
      29,   131,    30,    31,    32,    23,    24,    25,    90,    59,
      65,    26,    66,    67,    74,    68,    69,    70,    75,    78,
     113,    17,    71,    72,    73,    27,   110,   116,   115,   132,
      29,   125,    30,    31,    32,    67,   117,    68,    69,    70,
     120,   127,   136,   128,    71,    72,    73,   137,    67,   119,
      68,    69,    70,    20,    12,    47,    18,    71,    72,    73,
       0,   114,   129,    67,     0,    68,    69,    70,     0,     0,
       0,     0,    71,    72,    73,    67,     0,    68,    69,    70,
       0,    80,     0,     0,    71,    72,    73,    67,     0,    68,
      69,    70,     0,     0,     0,   118,    71,    72,    73,    67,
       0,    68,    69,    70,     0,     0,     0,     0,    71,    72,
      73
  };

  const short
  parser::yycheck_[] =
  {
      24,    59,    26,    27,     5,     5,     7,     7,     6,    26,
      27,    59,   111,    11,     3,    23,    24,     5,    33,     7,
      12,    13,    33,    11,    13,     0,    74,    25,    28,   128,
      18,    19,    33,    33,    58,    33,    34,   136,    62,    63,
      64,    58,     3,    67,    68,    69,    70,    71,    72,    73,
       3,    75,    76,    77,    11,    79,    66,    11,    82,    76,
      77,   114,    19,    21,    74,    26,    27,    19,    29,     5,
      33,     7,   130,    18,    19,     5,     6,     7,    34,   132,
      12,    11,    18,    19,     9,    10,    12,    13,   112,   113,
     114,    21,    33,    33,   118,    25,   113,    11,    28,    33,
      30,   125,    32,    33,    34,     5,     6,     7,   132,    11,
      22,    11,     3,     6,     3,     8,     9,    10,    13,    20,
       3,    21,    15,    16,    17,    25,    34,    20,    12,    21,
      30,    18,    32,    33,    34,     6,    22,     8,     9,    10,
      20,    18,    12,    31,    15,    16,    17,    22,     6,    20,
       8,     9,    10,    15,     2,    21,    12,    15,    16,    17,
      -1,     4,    20,     6,    -1,     8,     9,    10,    -1,    -1,
      -1,    -1,    15,    16,    17,     6,    -1,     8,     9,    10,
      -1,    12,    -1,    -1,    15,    16,    17,     6,    -1,     8,
       9,    10,    -1,    -1,    -1,    14,    15,    16,    17,     6,
      -1,     8,     9,    10,    -1,    -1,    -1,    -1,    15,    16,
      17
  };

  const signed char
  parser::yystos_[] =
  {
       0,    26,    27,    29,    37,    38,    39,    40,    41,    43,
      33,    42,    42,    33,     0,     3,    11,    21,    48,    19,
      38,    33,    44,     5,     6,     7,    11,    25,    28,    30,
      32,    33,    34,    45,    46,    47,    48,    49,    50,    51,
      53,    54,    55,    57,    58,    59,    34,    44,    12,    33,
      33,    49,    33,    49,    57,    49,    57,    33,    11,    11,
       5,     7,    11,    18,    19,    22,     3,     6,     8,     9,
      10,    15,    16,    17,     3,    13,    23,    24,    20,    19,
      12,    12,    18,    19,    52,    57,    33,    47,    51,    56,
      49,    60,    61,    49,    49,    45,    49,    49,    49,    49,
      49,    49,    49,    45,    51,    49,    57,    57,    49,    49,
      34,    12,    19,     3,     4,    12,    20,    22,    14,    20,
      20,    46,    49,    57,    61,    18,    49,    18,    31,    20,
       3,    49,    21,    46,    47,    61,    12,    22,    46
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    36,    37,    38,    38,    39,    39,    39,    39,    40,
      41,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      46,    46,    46,    47,    47,    47,    47,    47,    47,    48,
      48,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      50,    50,    51,    51,    51,    52,    52,    53,    54,    54,
      55,    56,    56,    57,    57,    57,    57,    57,    58,    58,
      58,    59,    59,    59,    60,    60,    61,    61
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     3,     0,     1,     1,     1,     3,
       2,     4,     2,     5,     0,     2,     1,     3,     1,     1,
       1,     1,     1,     3,     2,     2,     2,     2,     6,     3,
       5,     2,     3,     3,     3,     3,     1,     3,     1,     1,
       1,     3,     3,     5,     9,     0,     2,     5,     5,     7,
       9,     1,     1,     1,     3,     3,     2,     3,     3,     3,
       3,     1,     4,     4,     0,     1,     1,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\";\"", "\",\"",
  "\"--\"", "\"-\"", "\"++\"", "\"+\"", "\"*\"", "\"/\"", "\"(\"", "\")\"",
  "\"?\"", "\":\"", "\"<\"", "\">\"", "\"==\"", "\"=\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\"and\"", "\"or\"", "\"not\"", "\"extern\"",
  "\"def\"", "\"var\"", "\"global\"", "\"if\"", "\"else\"", "\"for\"",
  "\"id\"", "\"number\"", "\"then\"", "$accept", "startsymb", "program",
  "top", "definition", "external", "proto", "globalvar", "idseq", "stmts",
  "stmt", "assignment", "block", "exp", "vardefs", "binding", "initexp",
  "expif", "ifstmt", "forstmt", "init", "condexp", "relexp", "idexp",
  "optexp", "explist", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   117,   117,   120,   121,   124,   125,   126,   127,   132,
     135,   138,   143,   144,   148,   149,   152,   153,   156,   157,
     158,   159,   160,   163,   164,   165,   166,   167,   168,   172,
     173,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     197,   198,   201,   202,   203,   206,   207,   210,   216,   217,
     220,   223,   224,   227,   228,   229,   230,   231,   234,   235,
     236,   239,   240,   241,   244,   246,   249,   253
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1889 "parser.cpp"

#line 255 "parser.yy"


void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
