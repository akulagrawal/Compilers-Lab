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

        void insert_parameter(string parameter_name, string type, int level = 0){
            parameters.push_back(var_record(parameter_name, type, true, level));
        }

        void insert_variable(string var_name, string type, int level = 0){
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

        function_record* insert_function(string function_name) {
            function_record *r = new function_record();
            entries[function_name] = *r;
            return r; 
        }

        bool search_function(string function_name, function_record *function) {
            // If function exists in symbol table
            if (entries.count(function_name)) {
                // Set function = pointer to function in symbol table
                // Returns true
                function = &entries[function_name];
                return true;
            }
            else {
                // If not found returns not found (i.e. false)
                return false;
            }
        }

    } symtab;

    // Stores active function name
    string active_func_name;

    // Stores current level
    int level = 0;

    // Stores list of parameter of current function declaration
    list<var_record> active_func_param_list;

    // Stores list of arguments of function being called
    list<var_record> called_arg_list;

    // Stores true, If error is found while semantic checking
    bool errorFound = false;

    // Keep track of current line number
    int lineNo = 1;

    extern bool isInt(const char *type);
    extern bool isFloat(const char *type);
    extern bool isBoolean(const char *type);
    extern bool isErrorType(const char *type);
    extern bool isNoneType(const char *type);
    extern bool isMatch(const char *str1, const char *str2);
    extern void set_active_function(const char *str);

    extern bool isInt(string type);
    extern bool isFloat(string type);
    extern bool isBoolean(string type);
    extern bool isErrorType(string type);
    extern bool isNoneType(string type);
    extern bool isMatch(string str1, string str2);
    extern void set_active_function(string str);

    extern bool isInsideFunc();
    extern char* setErrorType();
    extern char* setNoErrorType();
    extern void reset_active_function();
    extern void errorLine();

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
    TYPE = 260,
    VOID = 261,
    OR = 262,
    IF = 263,
    ELSE = 264,
    FOR = 265,
    WHILE = 266,
    SWITCH = 267,
    CASE = 268,
    DEFAULT = 269
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 126 "c_lang.y" /* yacc.c:355  */

    struct {
        char* type;
        int len;
        char* sval;
    } type_id;

#line 254 "c_lang.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_LANG_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 271 "c_lang.tab.c" /* yacc.c:358  */

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   160

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  24
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   269

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
      17,    18,     2,     2,    19,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    22,    20,
       2,    21,    23,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    15,     2,    16,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   160,   160,   161,   162,   163,   167,   178,   185,   209,
     233,   250,   270,   292,   303,   307,   311,   315,   343,   389,
     426,   486,   500,   511,   528,   545,   546,   547,   548,   549,
     550,   554,   568,   582,   599,   613,   627,   644,   649,   653,
     654,   658,   659,   663,   664,   671,   672,   673,   677,   678,
     682,   683,   684,   685,   689,   690,   691,   692,   696
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "IDENTIFIER", "TYPE", "VOID",
  "OR", "IF", "ELSE", "FOR", "WHILE", "SWITCH", "CASE", "DEFAULT", "'{'",
  "'}'", "'('", "')'", "','", "';'", "'='", "':'", "'>'", "$accept",
  "START", "function_declaration", "function_head",
  "param_list_declaration", "param_declaration",
  "variable_declaration_list", "variable_declaration", "function_call",
  "arg_list", "statement", "conditional_statement", "loop_statement",
  "labeled_statement", "compound_statement", "statement_list",
  "expression_statement", "expression", "assignment_expression",
  "logical_expression", "relational_expression", "constant_expression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   123,   125,    40,    41,    44,
      59,    61,    58,    62
};
# endif

#define YYPACT_NINF -52

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-52)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      66,    -2,     8,    59,   -52,    15,   -52,   -52,    36,    25,
     -52,   -52,   -52,     3,    30,   -52,    39,    29,    80,    45,
      37,    67,    75,    79,    17,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,    35,   -52,    82,   -52,   -52,   -52,   100,
     -52,    91,   -52,   -52,    93,   111,   113,   115,    90,   117,
     119,   104,   123,     6,   123,   123,   -52,    58,   -52,   -52,
     -52,   -52,   -52,   101,   -52,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,   112,   110,   -52,   -52,   -52,   -52,   131,
      84,   121,     6,   122,   124,   -52,   -52,   -52,   125,   126,
     127,    78,    13,    78,   120,   -52,   -52,   -52,    95,   129,
      78,   128,   -52,   138,   130,   -52,   133,   118,    78,   -52,
      78,   -52,   132,    78,   -52,   135,   -52,   -52,    78,   -52,
     -52,   -52
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     0,     3,    15,     0,     0,
       1,     4,     5,     0,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     7,    43,    29,    30,    41,
      25,    26,    27,     0,    28,     0,    45,    46,    47,     0,
      10,     0,    13,    11,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    39,     0,     6,    42,
      44,    14,     8,     0,     9,    53,    51,    57,    55,    52,
      50,    21,    22,     0,     0,    48,    49,    56,    54,     0,
       0,     0,     0,     0,     0,    40,    12,    17,     0,     0,
       0,     0,     0,     0,     0,    18,    23,    24,     0,    31,
       0,     0,    34,     0,     0,    33,     0,     0,     0,    35,
       0,    58,     0,     0,    19,     0,    32,    36,     0,    38,
      20,    37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -52,   -52,   140,   -52,   134,    85,    76,   -52,   -52,    49,
     -33,   -52,   -52,   -52,   -52,   136,   -48,   -51,   -52,   -52,
     -52,   -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    41,    42,    27,     7,    28,    74,
      29,    30,    31,   105,    32,    33,    34,    35,    36,    37,
      38,   112
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,    81,     8,    83,    84,    82,    17,    18,    19,    17,
      80,    20,     9,    21,    22,    23,    17,    80,    24,    25,
      17,    18,    19,    26,    59,    20,    26,    21,    22,    23,
      13,   100,    24,    56,    92,    39,    45,    26,    17,    18,
      19,   101,    16,    20,    39,    21,    22,    23,    40,    51,
      24,    58,    46,    14,    52,    26,    15,    43,    99,    10,
     102,    17,    18,    19,     1,     2,    20,   109,    21,    22,
      23,     1,     2,    24,    85,   116,     6,   117,    26,    12,
     119,    17,    18,    19,    53,   121,    20,    47,    21,    22,
      23,    47,    54,    24,    71,    72,    55,    48,    26,    71,
      72,    49,    60,    50,    61,    49,    39,    50,    73,    62,
      63,    64,    63,   106,    65,    66,    67,    68,    69,    70,
      75,    76,    77,    78,    15,    79,    17,    80,    88,    89,
      96,    97,    87,   103,   104,    90,   115,    89,   108,    91,
      93,   111,    94,    11,    98,    95,   110,   107,    86,     0,
      44,     0,   113,   114,   118,   120,     0,     0,     0,     0,
      57
};

static const yytype_int8 yycheck[] =
{
      33,    52,     4,    54,    55,    53,     3,     4,     5,     3,
       4,     8,     4,    10,    11,    12,     3,     4,    15,    16,
       3,     4,     5,    20,    57,     8,    20,    10,    11,    12,
      15,    18,    15,    16,    82,     5,     7,    20,     3,     4,
       5,    92,    17,     8,     5,    10,    11,    12,    18,     4,
      15,    16,    23,    17,    17,    20,    20,    18,    91,     0,
      93,     3,     4,     5,     5,     6,     8,   100,    10,    11,
      12,     5,     6,    15,    16,   108,     0,   110,    20,     3,
     113,     3,     4,     5,    17,   118,     8,     7,    10,    11,
      12,     7,    17,    15,     4,     5,    17,    17,    20,     4,
       5,    21,    20,    23,     4,    21,     5,    23,    18,    18,
      19,    18,    19,    18,     3,     4,     3,     4,     3,     4,
       3,     4,     3,     4,    20,    21,     3,     4,    18,    19,
       4,     5,    20,    13,    14,     4,    18,    19,     9,    18,
      18,     3,    18,     3,    17,    20,    18,    98,    63,    -1,
      16,    -1,    22,    20,    22,    20,    -1,    -1,    -1,    -1,
      24
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    25,    26,    27,    30,    31,     4,     4,
       0,    26,    30,    15,    17,    20,    17,     3,     4,     5,
       8,    10,    11,    12,    15,    16,    20,    30,    32,    34,
      35,    36,    38,    39,    40,    41,    42,    43,    44,     5,
      18,    28,    29,    18,    28,     7,    23,     7,    17,    21,
      23,     4,    17,    17,    17,    17,    16,    39,    16,    34,
      20,     4,    18,    19,    18,     3,     4,     3,     4,     3,
       4,     4,     5,    18,    33,     3,     4,     3,     4,    21,
       4,    41,    40,    41,    41,    16,    29,    20,    18,    19,
       4,    18,    40,    18,    18,    20,     4,     5,    17,    34,
      18,    41,    34,    13,    14,    37,    18,    33,     9,    34,
      18,     3,    45,    22,    20,    18,    34,    34,    22,    34,
      20,    34
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    24,    25,    25,    25,    25,    26,    26,    27,    27,
      27,    27,    28,    28,    29,    30,    31,    32,    32,    32,
      32,    33,    33,    33,    33,    34,    34,    34,    34,    34,
      34,    35,    35,    35,    36,    36,    36,    37,    37,    38,
      38,    39,    39,    40,    40,    41,    41,    41,    42,    42,
      43,    43,    43,    43,    44,    44,    44,    44,    45
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     4,     3,     5,     5,
       4,     4,     3,     1,     2,     1,     3,     4,     5,     7,
       8,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     5,     7,     5,     5,     6,     7,     4,     3,     2,
       3,     1,     2,     1,     2,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1
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
        case 6:
#line 168 "c_lang.y" /* yacc.c:1646  */
    {
        level --;
        reset_active_function();
        if (!isErrorType((yyvsp[-3].type_id).type)) {
            if (!isNoneType((yyvsp[-1].type_id).type)) {
                if (!(isMatch((yyvsp[-3].type_id).type, (yyvsp[-1].type_id).type)))
                    cout << "Type mismatch of return type between " << (yyval.type_id).type << " and " << (yyvsp[-1].type_id).type << endl;
            }
        }
    }
#line 1443 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 179 "c_lang.y" /* yacc.c:1646  */
    {
        reset_active_function();
    }
#line 1451 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 186 "c_lang.y" /* yacc.c:1646  */
    {
        level ++;
        function_record *r;
        
        // Check if function already exists
        if (symtab.search_function((yyvsp[-3].type_id).sval, r)) {
            cout << "Error : Redeclaration of function : " << (yyvsp[-3].type_id).sval << " in line : " << lineNo << endl;
            r->function_return_type = setErrorType();
            (yyval.type_id).type = setErrorType();
        }
        else {
            r = symtab.insert_function((yyvsp[-3].type_id).sval);
            r->function_return_type = (yyvsp[-4].type_id).sval;

            // Add param_list_declaration to symbol_table corresponding to active function
            for (auto it = active_func_param_list.begin(); it != active_func_param_list.end(); it++) {
                r->insert_parameter(it->name, it->type, it->level);
            }
            (yyval.type_id).type = strdup((yyvsp[-4].type_id).sval);
        }

        set_active_function((yyvsp[-3].type_id).sval);
    }
#line 1479 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 210 "c_lang.y" /* yacc.c:1646  */
    {
        level ++;
        function_record *r;

        // Check if function already exists
        if (symtab.search_function((yyvsp[-3].type_id).sval, r)) {
            cout << "Error : Redeclaration of function : " << (yyvsp[-3].type_id).sval << " in line : " << lineNo << endl;
            r->function_return_type = setErrorType();
            (yyval.type_id).type = setErrorType();
        }
        else {
            r = symtab.insert_function((yyvsp[-3].type_id).sval);
            r->function_return_type = (yyvsp[-4].type_id).sval;

            // Add param_list_declaration to symbol_table corresponding to active function
            for (auto it = active_func_param_list.begin(); it != active_func_param_list.end(); it++) {
                r->insert_parameter(it->name, it->type, it->level);
            }
            (yyval.type_id).type = strdup((yyvsp[-4].type_id).sval);
        }

        set_active_function((yyvsp[-3].type_id).sval);
    }
#line 1507 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 234 "c_lang.y" /* yacc.c:1646  */
    {
        level ++;
        function_record *r;

        // Check if function already exists
        if (symtab.search_function((yyvsp[-2].type_id).sval, r)) {
            cout << "Error : Redeclaration of function : " << (yyvsp[-2].type_id).sval << " in line : " << lineNo << endl;
            (yyval.type_id).type = setErrorType();
        }
        else {
            r = symtab.insert_function((yyvsp[-2].type_id).sval);
            r->function_return_type = (yyvsp[-3].type_id).sval;
            (yyval.type_id).type = strdup((yyvsp[-3].type_id).sval);
        }
        set_active_function((yyvsp[-2].type_id).sval);
    }
#line 1528 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 251 "c_lang.y" /* yacc.c:1646  */
    {
        level ++;
        function_record *r;

        // Check if function already exists
        if (symtab.search_function((yyvsp[-2].type_id).sval, r)) {
            cout << "Error : Redeclaration of function : " << (yyvsp[-2].type_id).sval << " in line : " << lineNo << endl;
            (yyval.type_id).type = setErrorType();
        }
        else {
            r = symtab.insert_function((yyvsp[-2].type_id).sval);
            r->function_return_type = (yyvsp[-3].type_id).sval;
            (yyval.type_id).type = strdup((yyvsp[-3].type_id).sval);
        }
        set_active_function((yyvsp[-2].type_id).sval);
    }
#line 1549 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 271 "c_lang.y" /* yacc.c:1646  */
    {
        bool found = false;
        // Check if variable is repeated in parameter list
        for (auto it = active_func_param_list.begin(); it != active_func_param_list.end(); it++) {
            if (it -> name == (yyvsp[0].type_id).sval) {
                cout << "Redeclaration of parameter " << (yyvsp[0].type_id).sval << endl;
                (yyval.type_id).type = setErrorType();
                found = true;
                break;
            }
        }

        var_record param((yyvsp[0].type_id).sval, (yyvsp[0].type_id).type, /* is_parameter = */ true, level) ;
        active_func_param_list.push_back(param);
        (yyval.type_id).type = setNoErrorType();
        (yyval.type_id).len = (yyvsp[-2].type_id).len + 1;
        
        if (isErrorType((yyvsp[-2].type_id).type) || found) {
            (yyval.type_id).type = setErrorType();
        }
    }
#line 1575 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 293 "c_lang.y" /* yacc.c:1646  */
    {
        active_func_param_list.clear();
        (yyval.type_id).len = 1; 
        var_record param((yyvsp[0].type_id).sval, (yyvsp[0].type_id).type, /* is_parameter = */ true, level) ;
        active_func_param_list.push_back(param);
        (yyval.type_id).type = setNoErrorType();
    }
#line 1587 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 303 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = (yyvsp[-1].type_id).sval; (yyval.type_id).sval = (yyvsp[0].type_id).sval; }
#line 1593 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 311 "c_lang.y" /* yacc.c:1646  */
    {}
#line 1599 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 316 "c_lang.y" /* yacc.c:1646  */
    {
        function_record *r;
        string functionName = (yyvsp[-3].type_id).sval;
        
        // search for function declaration
        if (symtab.search_function(functionName, r)) {

            // If function's return type is ErrorType
            if (!isErrorType(r->function_return_type)) {

                // Check if param_list_declaration is empty
                if (r->parameters.empty())  {
                    (yyval.type_id).type = strdup(r->function_return_type.c_str());
                }
                else {
                    // Error
                    cout << "Too many arguments to function '" << functionName << "'\n";
                    (yyval.type_id).type = setErrorType();
                }
            }
        }
        else {
            // Function not found
            cout << "Function " << functionName << " is not declared\n";
            (yyval.type_id).type = setErrorType();
        }
    }
#line 1631 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 344 "c_lang.y" /* yacc.c:1646  */
    {
        function_record *r;
        string functionName = (yyvsp[-4].type_id).sval;
        
        // search for function declaration
        if (symtab.search_function(functionName, r)) {

            // If function's return type is ErrorType
            if (!isErrorType(r->function_return_type)) {
                
                // Check if param_list_declaration matches with arg_list
                if (r->parameters.size() > (yyvsp[-2].type_id).len) {
                    cout << "Too few arguments to function '" << functionName << "'\n";
                    (yyval.type_id).type = setErrorType();
                }
                else if (r->parameters.size() < (yyvsp[-2].type_id).len) {
                    cout << "Too many arguments to function '" << functionName << "'\n";
                    (yyval.type_id).type = setErrorType();
                }
                else {
                    // Match the datatypes of param_list_declaration and arg_list
                    auto param_it = r->parameters.begin();
                    auto arg_it = called_arg_list.begin();
                    while (param_it != r->parameters.end()) {

                        if (!isMatch(param_it->type, arg_it->type)) {
                            errorLine();
                            cout << "datatype mismatch for calling function : " << functionName << "\n";
                            (yyval.type_id).type = setErrorType();
                            break;
                        }
                        param_it ++;
                        arg_it ++;
                    }
                }
            }
        }
        else {
            // Function not found
            errorLine();
            cout << "Function " << functionName << " is not declared\n";
            (yyval.type_id).type = setErrorType();
        }
    }
#line 1680 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 390 "c_lang.y" /* yacc.c:1646  */
    {
        function_record *r;
        string functionName = (yyvsp[-3].type_id).sval;
        
        // search for function declaration
        if (symtab.search_function(functionName, r)) {

            // If function's return type is ErrorType
            if (!isErrorType(r->function_return_type)) {

                // Check if param_list_declaration is empty
                if (r->parameters.empty())  {
                    string return_type = r->function_return_type;
                    if ( !isMatch((yyvsp[-6].type_id).type, return_type) ) {
                        errorLine();
                        cout << "incompatible types when initializing type " << (yyvsp[-6].type_id).type << " using type " << return_type << endl;
                        (yyval.type_id).type = setErrorType();
                    }
                    else
                        (yyval.type_id).type = strdup(return_type.c_str());
                }
                else {
                    // Error
                    errorLine();
                    cout << "Too many arguments to function '" << functionName << "'\n";
                    (yyval.type_id).type = setErrorType();
                }
            }
        }
        else {
            // Function not found
            errorLine();
            cout << "Function " << functionName << " is not declared\n";
            (yyval.type_id).type = setErrorType();
        }
    }
#line 1721 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 427 "c_lang.y" /* yacc.c:1646  */
    {
        function_record *r;
        string functionName = (yyvsp[-4].type_id).sval;
        
        // search for function declaration
        if (symtab.search_function(functionName, r)) {

            // If function's return type is ErrorType
            if (!isErrorType(r->function_return_type)) {
                
                // Check if param_list_declaration matches with arg_list
                if (r->parameters.size() > (yyvsp[-2].type_id).len) {
                    cout << "Too few arguments to function '" << functionName << "'\n";
                    (yyval.type_id).type = setErrorType();
                }
                else if (r->parameters.size() < (yyvsp[-2].type_id).len) {
                    cout << "Too many arguments to function '" << functionName << "'\n";
                    (yyval.type_id).type = setErrorType();
                }
                else {
                    // Match the datatypes of param_list_declaration and arg_list
                    auto param_it = r->parameters.begin();
                    auto arg_it = called_arg_list.begin();
                    bool matched = true;
                    while (param_it != r->parameters.end()) {

                        if (!isMatch(param_it->type, arg_it->type)) {
                            errorLine();
                            cout << "datatype mismatch for calling function : " << functionName << "\n";
                            (yyval.type_id).type = setErrorType();
                            matched = false;
                            break;
                        }
                        param_it ++;
                        arg_it ++;
                    }
                    if (matched) {
                        string return_type = r->function_return_type;
                        if ( !isMatch((yyvsp[-7].type_id).type, return_type) ) {
                            errorLine();
                            cout << "incompatible types when initializing type " << (yyvsp[-7].type_id).type << " using type " << return_type << endl;
                            (yyval.type_id).type = setErrorType();
                        }
                        else
                            (yyval.type_id).type = strdup(return_type.c_str());
                        }
                }
            }
        }
        else {
            // Function not found
            errorLine();
            cout << "Function " << functionName << " is not declared\n";
            (yyval.type_id).type = setErrorType();
        }
    }
#line 1782 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 487 "c_lang.y" /* yacc.c:1646  */
    {
        called_arg_list.clear();
        (yyval.type_id).len = 1;

        // Search IDENTIFIER in the symbol_table
        // If found, Get the datatype of IDENTIFIER from symbol_table

        (yyval.type_id).type = setNoErrorType();
        string datatype = (yyvsp[0].type_id).type;
        
        var_record arg((yyvsp[0].type_id).sval, datatype, /* is_parameter = */ false, level) ;
        called_arg_list.push_back(arg);
    }
#line 1800 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 501 "c_lang.y" /* yacc.c:1646  */
    {
        called_arg_list.clear();
        (yyval.type_id).len = 1;

        (yyval.type_id).type = setNoErrorType();
        string datatype = (yyvsp[0].type_id).type;
        
        var_record arg((yyvsp[0].type_id).sval, datatype, /* is_parameter = */ false, level) ;
        called_arg_list.push_back(arg);
    }
#line 1815 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 512 "c_lang.y" /* yacc.c:1646  */
    {
        // Search IDENTIFIER in the symbol_table
        // If found, Get the datatype of IDENTIFIER from symbol_table

        string datatype = (yyvsp[0].type_id).type;
        (yyval.type_id).type = setNoErrorType();

        var_record arg((yyvsp[0].type_id).sval, datatype, /* is_parameter = */ false, level) ;

        called_arg_list.push_back(arg);
        (yyval.type_id).len = (yyvsp[-2].type_id).len + 1;
        
        if (isErrorType((yyvsp[-2].type_id).type)) {
            (yyval.type_id).type = setErrorType();
        }
    }
#line 1836 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 529 "c_lang.y" /* yacc.c:1646  */
    {
        string datatype = (yyvsp[0].type_id).type;
        (yyval.type_id).type = setNoErrorType();

        var_record arg((yyvsp[0].type_id).sval, datatype, /* is_parameter = */ false, level) ;

        called_arg_list.push_back(arg);
        (yyval.type_id).len = (yyvsp[-2].type_id).len + 1;
        
        if (isErrorType((yyvsp[-2].type_id).type)) {
            (yyval.type_id).type = setErrorType();
        }
    }
#line 1854 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 555 "c_lang.y" /* yacc.c:1646  */
    {
        if (!isErrorType((yyvsp[-2].type_id).type)) {
            if ( isInt((yyvsp[-2].type_id).type) || isFloat((yyvsp[-2].type_id).type) ) {
                (yyval.type_id).type = setNoErrorType();
            }
            else {
                yyerror("int expected in expression of if-else");
                (yyval.type_id).type = setErrorType();
            }
        }
        else
            (yyval.type_id).type = setErrorType();
    }
#line 1872 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 569 "c_lang.y" /* yacc.c:1646  */
    {
        if (!isErrorType((yyvsp[-4].type_id).type)) {
            if ( isInt((yyvsp[-4].type_id).type) || isFloat((yyvsp[-4].type_id).type) ) {
                (yyval.type_id).type = setNoErrorType();
            }
            else {
                yyerror("int expected in expression of if-else");
                (yyval.type_id).type = setErrorType();
            }
        }
        else
            (yyval.type_id).type = setErrorType();
    }
#line 1890 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 583 "c_lang.y" /* yacc.c:1646  */
    {
        if (!isErrorType((yyvsp[-2].type_id).type)) {
            if (isInt((yyvsp[-2].type_id).type)) {
                (yyval.type_id).type = setNoErrorType();
            }
            else {
                yyerror("int expected in expression of switch case");
                (yyval.type_id).type = setErrorType();
            }
        }
        else
            (yyval.type_id).type = setErrorType();
    }
#line 1908 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 600 "c_lang.y" /* yacc.c:1646  */
    { 
        if (!isErrorType((yyvsp[-2].type_id).type)) {
            if (isInt((yyvsp[-2].type_id).type) || isFloat((yyvsp[-2].type_id).type)) {
                (yyval.type_id).type = setNoErrorType();
            }
            else {
                yyerror("int expected in expression of while statement");
                (yyval.type_id).type = setErrorType();
            }
        }
        else
            (yyval.type_id).type = setErrorType();
    }
#line 1926 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 614 "c_lang.y" /* yacc.c:1646  */
    {
        if (!isErrorType((yyvsp[-3].type_id).type)) {
            if (isInt((yyvsp[-2].type_id).type) || isFloat((yyvsp[-2].type_id).type) || isNoneType((yyvsp[-2].type_id).type)) {
                (yyval.type_id).type = setNoErrorType();
            }
            else {
                yyerror("Type error in condition of for loop");
                (yyval.type_id).type = setErrorType();
            }
        }
        else
            (yyval.type_id).type = setErrorType();
    }
#line 1944 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 628 "c_lang.y" /* yacc.c:1646  */
    {
        if (!isErrorType((yyvsp[-4].type_id).type)) {
            if (isInt((yyvsp[-3].type_id).type) || isFloat((yyvsp[-3].type_id).type) || isNoneType((yyvsp[-3].type_id).type)) {
                (yyval.type_id).type = setNoErrorType();
            }
            else {
                yyerror("Type error in condition of for loop");
                (yyval.type_id).type = setErrorType();
            }
        }
        else
            (yyval.type_id).type = setErrorType();
    }
#line 1962 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 644 "c_lang.y" /* yacc.c:1646  */
    {
        if (!isMatch((yyvsp[-2].type_id).type, "int")) {
            yyerror("int expected in switch case");
        }
    }
#line 1972 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 653 "c_lang.y" /* yacc.c:1646  */
    {}
#line 1978 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 654 "c_lang.y" /* yacc.c:1646  */
    {}
#line 1984 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 663 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup("None"); }
#line 1990 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 664 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup((yyvsp[-1].type_id).type); }
#line 1996 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 671 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup((yyvsp[0].type_id).type); }
#line 2002 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 672 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup("int"); }
#line 2008 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 673 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup("int"); }
#line 2014 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 677 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup((yyvsp[0].type_id).type); }
#line 2020 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 678 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup((yyvsp[-2].type_id).type); }
#line 2026 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 696 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup("num"); }
#line 2032 "c_lang.tab.c" /* yacc.c:1646  */
    break;


#line 2036 "c_lang.tab.c" /* yacc.c:1646  */
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
#line 698 "c_lang.y" /* yacc.c:1906  */


int main(int argc, char **argv) {

    char *filename = (char*)malloc(sizeof(char)*20);
    strcpy(filename, "input.txt");

    // Open a file handle to a particular file:
    FILE *myfile = fopen(filename, "r");
    // Make sure it is valid:
    if (!myfile) {
        print(filename, "does not exists.");
        return -1;
    }
    // Set Flex to read from it instead of defaulting to STDIN:
    yyin = myfile;

    // Parse through the input:
    while(!feof(yyin))  {
        yyparse();
    }
  
}

void yyerror(const char *s) {
  print("", s);
//   exit(-1);
}

bool isInt(const char *type) {
    if (isMatch(type, "int"))    return true;
    else                        return false;
}
bool isFloat(const char *type) {
    if (isMatch(type, "float"))    return true;
    else                        return false;
}
bool isBoolean(const char *type) {
    if (isMatch(type, "bool"))    return true;
    else                        return false;
}
bool isErrorType(const char *type) {
    if (isMatch(type, "ErrorType"))    return true;
    else                        return false;
}
bool isNoneType(const char *type) {
    if (isMatch(type, "None"))    return true;
    else                        return false;
}
bool isMatch(const char *str1, const char *str2) {
    return !strcmp(str1, str2);
}
void set_active_function(const char *str) {
    active_func_name = str;
}

bool isInt(string type) {
    if (isMatch(type, "int"))    return true;
    else                        return false;
}
bool isFloat(string type) {
    if (isMatch(type, "float"))    return true;
    else                        return false;
}
bool isBoolean(string type) {
    if (isMatch(type, "bool"))    return true;
    else                        return false;
}
bool isErrorType(string type) {
    if (isMatch(type, "ErrorType"))    return true;
    else                        return false;
}
bool isNoneType(string type) {
    if (isMatch(type, "None"))    return true;
    else                        return false;
}
bool isMatch(string str1, string str2) {
    return str1 == str2;
}
void set_active_function(string str) {
    active_func_name = str;
}

char* setErrorType() {
    errorFound = true;
    return strdup("ErrorType");
}
char* setNoErrorType() {
    return strdup("NoErrorType");
}
bool isInsideFunc() {
    return !(active_func_name == "");
}
void reset_active_function() {
    active_func_name = "";
}
void errorLine() {
    cout << "Error at line " << lineNo << " : ";
}
