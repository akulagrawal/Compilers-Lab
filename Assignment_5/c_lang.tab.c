/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "c_lang.y" /* yacc.c:339  */

    #include <bits/stdc++.h>
    #include <string>
    #define print(str, val) \
        std::cout << str << " " <<  val << std::endl;

    // Declare stuff from Flex that Bison needs to know about:
    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;
    void yyerror(const char *s);
    using namespace std;

    // Stores active function name
    string active_func_name;

    struct var_record {
        string name;
        string type;
        bool is_parameter;
        int level;

        var_record(string name, string type, bool is_parameter = true, int level = 0){
            this -> name = name;
            this -> type = type;
            this -> is_parameter = is_parameter;
            this -> level = level;
        }
    };

    struct function_record {
        string function_return_type;
        list<var_record> parameters;
        list<var_record> local_variables;

        void insert_parameter(string parameter_name, string type){
            parameters.push_back(var_record(parameter_name, type));
        }

        void insert_variable(string var_name, string type, int level){
            local_variables.push_back(var_record(var_name, type, false, level));
        }

        var_record& search_param(string parameter_name) {
            for(auto it = parameters.begin(); it != parameters.end(); ++it){
                if(it -> name == parameter_name){
                    return *it;
                }
            }
        }

        var_record& search_variable(string var_name) {
            for(auto it = local_variables.begin(); it != local_variables.end(); ++it){
                if(it -> name  == var_name){
                    return *it;
                }
            }
        }
    };

    struct symbol_table {
        unordered_map<string, function_record> entries;

        function_record& insert_function(string function_name) {
            assert(!entries.count(function_name));
            return entries[function_name];
        }

        bool search_function(string function_name, function_record& function) {
            // If function exists in symbol table
            if (entries.count(function_name)) {
                // Set function = pointer to function in symbol table
                // Returns true
                function = entries[function_name];
                return true;
            }
            else {
                // If not found returns not found (i.e. false)
                return false;
            }
        }

    } symtab;

    extern bool isInt(char *type);
    extern bool isFloat(char *type);
    extern bool isBoolean(char *type);
    extern bool isErrorType(char *type);
    extern bool isNoneType(char *type);
    extern char* setErrorType();
    extern char* setNoErrorType();

    /* Intermediate Code Generation. */
    /* Quadruples. */
    struct quadruple {
        string _operator;
        string _arg1;
        string _arg2;
        string _result;

        quadruple(){}

        quadruple(string op, string arg1, string arg2, string result){
            this -> _operator = op;
            this -> _arg1 = arg1;
            this -> _arg2 = arg2;
            this -> _result = result;
        }
    };

    vector<quadruple> quadruples;

    /* Indices of associated quadruples. */
    struct indexlist {
        vector<int> indexes;
    };

    /* Temporary variables for intermediate code. */
    int curr_temp = 0;
    string get_next_temp(){
        curr_temp += 1;
        return "t" + std::to_string(curr_temp);
    }

#line 191 "c_lang.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "c_lang.tab.h".  */
#ifndef YY_YY_C_LANG_TAB_H_INCLUDED
# define YY_YY_C_LANG_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    IDENTIFIER = 259,
    INT = 260,
    FLOAT = 261,
    OR = 262,
    IF = 263,
    ELSE = 264,
    FOR = 265,
    WHILE = 266,
    SWITCH = 267,
    CASE = 268,
    DEFAULT = 269,
    BREAK = 270,
    CONTINUE = 271,
    AND = 272,
    REL_OP = 273
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 126 "c_lang.y" /* yacc.c:355  */

    struct {
        struct indexlist * indexlist;
        char* type;
        int val;
        int index;
        char* sval;
    } type_id;

#line 260 "c_lang.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_LANG_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 277 "c_lang.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   166

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  124

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   273

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      21,    22,     2,     2,    23,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,    24,
       2,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    19,     2,    20,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   170,   170,   171,   172,   173,   177,   178,   182,   183,
     187,   191,   192,   196,   200,   204,   208,   209,   213,   214,
     215,   216,   220,   221,   225,   226,   227,   228,   232,   236,
     237,   241,   247,   255,   265,   277,   285,   294,   301,   312,
     328,   343,   348,   352,   356,   363,   367,   374,   379,   390,
     395,   400,   408,   415,   425,   430,   435,   440,   448,   452,
     459,   464,   469,   474,   482
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "IDENTIFIER", "INT", "FLOAT",
  "OR", "IF", "ELSE", "FOR", "WHILE", "SWITCH", "CASE", "DEFAULT", "BREAK",
  "CONTINUE", "AND", "REL_OP", "'{'", "'}'", "'('", "')'", "','", "';'",
  "'='", "':'", "$accept", "START", "function_declaration",
  "function_head", "func_name", "param_list_declaration",
  "param_declaration", "variable_declaration_list", "variable_declaration",
  "datatype", "function_call", "arg_list", "statement",
  "conditional_statement", "if_exp", "else_mark", "loop_statement",
  "FOREXP", "WHILEEXP", "labeled_statement", "compound_statement",
  "statement_list", "expression_statement", "expression",
  "assignment_expression", "logical_expression", "logical_operation",
  "relational_expression", "constant_expression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   123,
     125,    40,    41,    44,    59,    61,    58
};
# endif

#define YYPACT_NINF -53

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-53)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      58,   -53,   -53,    51,   -53,    -7,   -53,   -53,    19,   -53,
     -53,   -53,    35,    12,    21,     4,    -1,    37,    47,    72,
      78,    69,    89,    70,   -53,   -53,   -53,   117,   -53,   -53,
     -53,   136,   -53,    10,   136,   -53,   -53,    92,   -53,    99,
     -53,   -53,   -53,   -53,    55,   -53,   -53,    62,    67,    82,
      11,    84,    88,   104,     6,   104,   104,   -53,   110,   136,
     -53,   114,    85,   126,     1,   136,   115,   -53,   -53,   -53,
     -53,   -53,    91,   -53,   139,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   121,   107,   -53,   -53,   -53,   -53,   129,     6,
     130,   131,   136,   -53,   -53,   150,   -53,   136,   -53,   136,
     -53,    58,   -53,   -53,   132,   153,   -53,   -53,   -53,   136,
     -53,   137,   -53,   -53,   -53,   -53,   -53,   -53,    30,   135,
     109,   -53,   138,   -53
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    16,    17,     0,     2,     0,     3,    14,     0,     1,
       4,     5,     0,    10,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     7,    47,    29,     0,    30,    45,
      24,     0,    25,     0,     0,    26,    27,     0,    28,     0,
      49,    50,    51,    15,     0,    58,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,     0,     0,
      43,     0,     0,    31,     0,     0,     0,    36,     6,    46,
      48,     9,     0,    12,     0,    63,    61,    57,    55,    62,
      60,    22,     0,     0,    52,    53,    56,    54,     0,     0,
       0,     0,     0,    42,    44,     0,    35,     0,    37,     0,
       8,     0,    13,    18,     0,     0,    34,    39,    40,     0,
      41,     0,    32,    38,    11,    19,    23,    33,     0,     0,
       0,    20,     0,    21
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -53,   -53,   158,   -53,   -53,   -53,    63,    50,   -53,     0,
     -53,    45,   -30,   -53,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   142,   -52,   -28,   -53,   -53,   151,   -53,   -53
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    14,    72,    73,    26,     7,    27,
      28,    83,    29,    30,    31,    97,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    52,    42,    58
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       8,    63,    89,     8,    67,    66,    45,    69,    45,    15,
      64,    45,    12,    15,    64,    81,    46,    49,    46,    49,
      50,    46,    47,    13,    51,    88,    51,    90,    91,    93,
      25,    69,    65,    82,    81,    98,    43,   107,    15,    16,
       1,     2,    44,    17,    74,    18,    19,    20,    21,    22,
       6,     9,   119,    11,    23,    24,     1,     2,    53,    25,
       1,     2,   110,     1,     2,    75,    76,   112,    54,   113,
      77,    78,    57,    15,    16,     1,     2,    71,    17,   117,
      18,    19,    20,    21,    22,    79,    80,    84,    85,    23,
      60,    86,    87,    55,    25,    15,    16,     1,     2,    56,
      17,    74,    18,    19,    20,    21,    22,    15,    64,    43,
      95,    23,    68,   100,   101,    59,    25,    15,    16,     1,
       2,    62,    17,    70,    18,    19,    20,    21,    22,   104,
     105,   122,   105,    23,    94,    96,    92,    99,    25,    15,
      16,     1,     2,   102,    17,   103,    18,    19,    20,    21,
      22,   106,   108,   109,   111,    23,   115,   116,   118,   121,
      25,    10,   123,   120,   114,    61,    48
};

static const yytype_uint8 yycheck[] =
{
       0,    31,    54,     3,    34,    33,     7,    37,     7,     3,
       4,     7,    19,     3,     4,     4,    17,    18,    17,    18,
      21,    17,    18,     4,    25,    53,    25,    55,    56,    59,
      24,    61,    22,    22,     4,    65,    24,    89,     3,     4,
       5,     6,    21,     8,    44,    10,    11,    12,    13,    14,
       0,     0,    22,     3,    19,    20,     5,     6,    21,    24,
       5,     6,    92,     5,     6,     3,     4,    97,    21,    99,
       3,     4,     3,     3,     4,     5,     6,    22,     8,   109,
      10,    11,    12,    13,    14,     3,     4,     3,     4,    19,
      20,     3,     4,    21,    24,     3,     4,     5,     6,    21,
       8,   101,    10,    11,    12,    13,    14,     3,     4,    24,
      25,    19,    20,    22,    23,    26,    24,     3,     4,     5,
       6,     4,     8,    24,    10,    11,    12,    13,    14,    22,
      23,    22,    23,    19,    20,     9,    26,    22,    24,     3,
       4,     5,     6,     4,     8,    24,    10,    11,    12,    13,
      14,    22,    22,    22,     4,    19,    24,     4,    21,    24,
      24,     3,    24,   118,   101,    23,    15
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    28,    29,    30,    34,    35,    36,     0,
      29,    34,    19,     4,    31,     3,     4,     8,    10,    11,
      12,    13,    14,    19,    20,    24,    34,    36,    37,    39,
      40,    41,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    54,    24,    21,     7,    17,    18,    53,    18,
      21,    25,    53,    21,    21,    21,    21,     3,    55,    26,
      20,    48,     4,    39,     4,    22,    50,    39,    20,    39,
      24,    22,    32,    33,    36,     3,     4,     3,     4,     3,
       4,     4,    22,    38,     3,     4,     3,     4,    50,    49,
      50,    50,    26,    39,    20,    25,     9,    42,    39,    22,
      22,    23,     4,    24,    22,    23,    22,    49,    22,    22,
      39,     4,    39,    39,    33,    24,     4,    39,    21,    22,
      38,    24,    22,    24
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    27,    28,    28,    28,    28,    29,    29,    30,    30,
      31,    32,    32,    33,    34,    35,    36,    36,    37,    37,
      37,    37,    38,    38,    39,    39,    39,    39,    39,    39,
      39,    40,    40,    40,    41,    42,    43,    43,    43,    44,
      45,    46,    46,    47,    47,    48,    48,    49,    49,    50,
      50,    50,    51,    51,    52,    52,    52,    52,    53,    53,
      54,    54,    54,    54,    55
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     4,     3,     5,     4,
       1,     3,     1,     2,     1,     3,     1,     1,     4,     5,
       7,     8,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     4,     5,     4,     1,     2,     3,     4,     4,
       4,     4,     3,     2,     3,     1,     2,     1,     2,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     1,     1,
       3,     3,     3,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 15:
#line 204 "c_lang.y" /* yacc.c:1646  */
    {}
#line 1446 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 208 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup("int"); }
#line 1452 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 209 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup("float"); }
#line 1458 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 229 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
    }
#line 1466 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 233 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
    }
#line 1474 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 242 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val;
        int gotoindex = (yyvsp[-1].type_id).index;
        quadruples[gotoindex]._result = to_string(gotoindex + (yyvsp[0].type_id).val + 1);
    }
#line 1484 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 248 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-3].type_id).val + (yyvsp[-2].type_id).val + (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val;
        int gotoindex1 = (yyvsp[-3].type_id).index;
        quadruples[gotoindex1]._result = to_string(gotoindex1 + (yyvsp[-2].type_id).val + (yyvsp[-1].type_id).val + 1);
        int gotoindex2 = (yyvsp[-1].type_id).index;
        quadruples[gotoindex2]._result = to_string(gotoindex2 + (yyvsp[0].type_id).val + 1);
    }
#line 1496 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 256 "c_lang.y" /* yacc.c:1646  */
    {
        if (strcmp((yyvsp[-2].type_id).type, "num")) {
            yyerror("int or boolean expected in expression of switch case");
        }

    }
#line 1507 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 266 "c_lang.y" /* yacc.c:1646  */
    {
        if (strcmp((yyvsp[-1].type_id).type, "num")) {
            yyerror("int or boolean expected in expression of if-else");
        }

        (yyval.type_id).index = quadruples.size();
        (yyval.type_id).val = (yyvsp[-1].type_id).val + 1;
        quadruples.push_back(quadruple("if0", "expres", "", ""));
    }
#line 1521 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 278 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        (yyval.type_id).index = quadruples.size();
        quadruples.push_back(quadruple("go", "", "", ""));
    }
#line 1531 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 286 "c_lang.y" /* yacc.c:1646  */
    {

      (yyval.type_id).val = (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val;
        int gotoindex = (yyvsp[-1].type_id).index;
        cout<<"$1.index :"<<(yyvsp[-1].type_id).index<<" $2.val= "<<(yyvsp[0].type_id).val<<endl;
        quadruples[gotoindex]._result = to_string(gotoindex + (yyvsp[0].type_id).val + 1);

      }
#line 1544 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 295 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val;
          int gotoindex = (yyvsp[-2].type_id).index;
          cout<<"$1.index :"<<(yyvsp[-2].type_id).index<<" $2.val= "<<(yyvsp[0].type_id).val<<endl;
          quadruples[gotoindex]._result = to_string(gotoindex + (yyvsp[0].type_id).val + 1);
      }
#line 1555 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 302 "c_lang.y" /* yacc.c:1646  */
    {
          (yyval.type_id).val = (yyvsp[-3].type_id).val + (yyvsp[-2].type_id).val+(yyvsp[0].type_id).val;
            int gotoindex = (yyvsp[-3].type_id).index;
            cout<<"$1.index :"<<(yyvsp[-3].type_id).index<<" $2.val= "<<(yyvsp[-2].type_id).val<<endl;
            quadruples[gotoindex]._result = to_string(gotoindex + (yyvsp[-2].type_id).val+ (yyvsp[0].type_id).val + 1);
        }
#line 1566 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 312 "c_lang.y" /* yacc.c:1646  */
    {
            if (strcmp((yyvsp[0].type_id).type, "num") && strcmp((yyvsp[0].type_id).type, "None")) {
                yyerror("Type error in condition of for loop");
            }
            (yyval.type_id).index = quadruples.size();
            (yyval.type_id).val = (yyvsp[-1].type_id).val+ (yyvsp[0].type_id).val+1;
            quadruple temp;
            temp._operator = "ifz";
            temp._arg1 = "expres";
            temp._arg2 = "";
            temp._result = "";
            quadruples.push_back(temp);
        }
#line 1584 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 328 "c_lang.y" /* yacc.c:1646  */
    {
            if (strcmp((yyvsp[-1].type_id).type, "num")) {
                yyerror("int or boolean expected in expression of while statement");
            }
            (yyval.type_id).index = quadruples.size();
            (yyval.type_id).val = (yyvsp[-1].type_id).val+1;
            quadruple temp;
            temp._operator = "ifz";
            temp._arg1 = "expres";
            temp._arg2 = "";
            temp._result = "";
            quadruples.push_back(temp);
        }
#line 1602 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 343 "c_lang.y" /* yacc.c:1646  */
    {
        if (strcmp((yyvsp[-2].type_id).type, "int")) {
            yyerror("int expected in switch case");
        }
    }
#line 1612 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 353 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 0;
    }
#line 1620 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 357 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val;
    }
#line 1628 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 364 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
    }
#line 1636 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 368 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val;
    }
#line 1644 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 375 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 0;
        (yyval.type_id).type = strdup("None");
    }
#line 1653 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 380 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val;
        (yyval.type_id).type = strdup((yyvsp[-1].type_id).type);
    }
#line 1662 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 391 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 1671 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 396 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).type = strdup("num");
    }
#line 1680 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 401 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).type = strdup("num");
    }
#line 1689 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 409 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 2;
        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
        quadruples.push_back(quadruple("=", string((yyvsp[0].type_id).sval), "", string((yyvsp[-2].type_id).sval)));
        quadruples.push_back(quadruple("=", string((yyvsp[-2].type_id).sval), "", "expres"));
    }
#line 1700 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 416 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 2;
        (yyval.type_id).type = strdup((yyvsp[-2].type_id).type);
        quadruples.push_back(quadruple("=", string((yyvsp[0].type_id).sval), "", string((yyvsp[-2].type_id).sval)));
        quadruples.push_back(quadruple("=", string((yyvsp[-2].type_id).sval), "", "expres"));
    }
#line 1711 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 426 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        quadruples.push_back(quadruple(string((yyvsp[-1].type_id).sval), string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), "expres"));
    }
#line 1720 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 431 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        quadruples.push_back(quadruple(string((yyvsp[-1].type_id).sval), string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), "expres"));
    }
#line 1729 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 436 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        quadruples.push_back(quadruple(string((yyvsp[-1].type_id).sval), string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), "expres"));
    }
#line 1738 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 441 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        quadruples.push_back(quadruple(string((yyvsp[-1].type_id).sval), string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), "expres"));
    }
#line 1747 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 449 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).sval = strdup((yyvsp[0].type_id).sval);
    }
#line 1755 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 453 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).sval = strdup((yyvsp[0].type_id).sval);
    }
#line 1763 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 460 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        quadruples.push_back(quadruple(string((yyvsp[-1].type_id).sval), string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), "expres"));
    }
#line 1772 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 465 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        quadruples.push_back(quadruple(string((yyvsp[-1].type_id).sval), string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), "expres"));
    }
#line 1781 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 470 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        quadruples.push_back(quadruple(string((yyvsp[-1].type_id).sval), string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), "expres"));
    }
#line 1790 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 475 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        quadruples.push_back(quadruple(string((yyvsp[-1].type_id).sval), string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), "expres"));
    }
#line 1799 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 482 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup("num"); }
#line 1805 "c_lang.tab.c" /* yacc.c:1646  */
    break;


#line 1809 "c_lang.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 484 "c_lang.y" /* yacc.c:1906  */


int main(int argc, char **argv) {

    char *filename = (char*)malloc(sizeof(char)*20);
    strcpy(filename, "input.txt");

    // Open a file handle to a particular file:
    FILE *myfile = fopen(filename, "r");
    // Make sure it is valid:
    if (!myfile) {
        print("I can't open ", filename);
        return -1;
    }
    // Set Flex to read from it instead of defaulting to STDIN:
    yyin = myfile;

    // Parse through the input:
    while(!feof(yyin))  {
        yyparse();
    }

    cout << "Intermediate Code in Quadruple Format:" << "\n";
    for(int i = 0; i < quadruples.size(); ++i){
        quadruple quad = quadruples[i];
        cout << setw(3) << i << "      " << setw(3) << quad._operator << " | " << setw(6) << quad._arg1 << " | " << setw(6) << quad._arg2 << " | " << setw(6) << quad._result << "\n";
    }

}

void yyerror(const char *s) {
  print("", s);
//   exit(-1);
}

bool isInt(char *type) {
    if (strcmp(type, "int"))    return false;
    else                        return true;
}
bool isFloat(char *type) {
    if (strcmp(type, "float"))    return false;
    else                        return true;
}
bool isBoolean(char *type) {
    if (strcmp(type, "bool"))    return false;
    else                        return true;
}
bool isErrorType(char *type) {
    if (strcmp(type, "ErrorType"))    return false;
    else                        return true;
}
bool isNoneType(char *type) {
    if (strcmp(type, "None"))    return false;
    else                        return true;
}
char* setErrorType() {
    return strdup("ErrorType");
}
char* setNoErrorType() {
    return strdup("NoErrorType");
}
