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
#line 1 "bison_dbms.y" /* yacc.c:339  */

    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #define print(str, val) \
    printf("%s %s\n", str, val);
    #define TRUE 1
    #define FALSE 0

    #define NUMBER 1
    #define STRING 0

    // Declare stuff from Flex that Bison needs to know about:
    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;
    extern void eat_till_semi();

    void yyerror(const char *s);

    extern void insert_header (FILE *filename);
    extern void insert_footer (FILE *filename);
    extern void extract_column ();

    char schema[1024];
    char column_str[1024];
    char column[30][30];
    int num_column = 0;
    int position = 0;
    char condition[100][50];
    int condition_ptr = 0;
    // --------------------------------------------------------------------

    #define MAX_COLS 10
    #define MAX_COL_LEN 10
    #define MAX_FILES 10
    #define MAX_FILES_LEN 10

    char data_type[MAX_FILES][MAX_COLS];
    char col_name[MAX_FILES][MAX_COLS][MAX_COL_LEN];
    char file_name[MAX_FILES][MAX_FILES_LEN];
    int num_files = 0;
    extern int gettype(char* table_name, char* col);
    extern int getcolindex(int index, char* col);
    extern int getfileindex(char* name);
    extern void readcsv(char* name);
    extern int isnum(char *);
    

#line 117 "bison_dbms.tab.c" /* yacc.c:339  */

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
   by #include "bison_dbms.tab.h".  */
#ifndef YY_YY_BISON_DBMS_TAB_H_INCLUDED
# define YY_YY_BISON_DBMS_TAB_H_INCLUDED
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
    SELECT = 258,
    PROJECT = 259,
    CARTESIAN_PRODUCT = 260,
    EQUI_JOIN = 261,
    AND = 262,
    LT_EQ = 263,
    EQ = 264,
    NEQ = 265,
    LP = 266,
    RP = 267,
    LAB = 268,
    RAB = 269,
    SIC = 270,
    DIC = 271,
    COMMA = 272,
    SEMI = 273,
    NUM = 274,
    ID = 275,
    DOT = 276,
    MINUS = 277,
    ARITH_OP = 278
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 60 "bison_dbms.y" /* yacc.c:355  */

    int ival;
    float fval;
    char *sval;

#line 187 "bison_dbms.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_DBMS_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 204 "bison_dbms.tab.c" /* yacc.c:358  */

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   77

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  24
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  32
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  83

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   104,   104,   105,   107,   177,   199,   214,   329,   334,
     336,   342,   344,   349,   350,   356,   357,   359,   360,   367,
     368,   369,   371,   372,   373,   375,   376,   377,   378,   379,
     381,   382,   384
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SELECT", "PROJECT", "CARTESIAN_PRODUCT",
  "EQUI_JOIN", "AND", "LT_EQ", "EQ", "NEQ", "LP", "RP", "LAB", "RAB",
  "SIC", "DIC", "COMMA", "SEMI", "NUM", "ID", "DOT", "MINUS", "ARITH_OP",
  "$accept", "STMT_LIST", "STMT", "TABLE", "CONDITION_LIST", "LOGICAL_OP",
  "CONDITION", "CONDITION_LIST_EQ", "CONDITION_EQ", "EXPR", "ARITHMETIC",
  "OP", "ATTR_LIST", "ATTR", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278
};
# endif

#define YYPACT_NINF -52

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-52)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       9,    -7,    -6,     6,     8,    40,     5,   -52,     3,    21,
     -52,    30,   -52,   -52,     3,    17,    29,    37,   -52,    31,
      32,    16,    34,   -52,   -52,   -52,   -52,   -52,    13,    36,
     -52,     3,    39,    21,    41,    35,   -52,    15,    14,   -52,
     -52,     8,   -52,     8,   -52,     8,     4,    38,    42,    43,
      43,    44,    45,    47,     4,    46,    49,    37,   -52,   -52,
     -52,   -52,    33,    48,    50,    52,    51,    54,     4,   -52,
     -52,   -52,   -52,    60,     8,   -52,    53,    58,    55,    56,
      57,   -52,   -52
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     8,     0,     0,
       9,     0,     1,     3,     0,     0,     0,    11,    32,     0,
      31,     0,     0,    29,    25,    26,    27,    28,     0,     0,
      12,     0,     0,     0,     0,     0,    13,     0,    24,    14,
      19,     0,    10,     0,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,    21,    20,
      23,    22,     0,     0,     0,     0,     0,     0,     0,     4,
       5,     6,    17,     0,     0,    15,     0,     0,     0,     0,
       0,     7,    18
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -52,    66,   -52,   -41,   -13,    -4,   -52,   -51,   -52,   -52,
     -11,   -52,    22,   -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,    11,    16,    31,    17,    56,    57,    39,
      40,    28,    19,    20
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      51,    22,    52,    65,    53,    -2,     1,     8,     2,     3,
       1,     7,     2,     3,    14,    54,     4,    75,    42,     9,
       4,    34,    35,    15,    55,    23,    24,    25,    10,    37,
      26,    27,    38,    77,    47,    48,    49,    50,    60,    61,
      12,    18,    21,    29,    30,    32,    36,    41,    46,    33,
      43,    69,    45,    68,    58,    44,    62,    63,    59,    64,
       0,     0,    38,    67,    72,    74,    70,    66,    71,    76,
      79,    73,    13,    78,    81,     0,    80,    82
};

static const yytype_int8 yycheck[] =
{
      41,    14,    43,    54,    45,     0,     1,    13,     3,     4,
       1,    18,     3,     4,    11,    11,    11,    68,    31,    13,
      11,     5,     6,    20,    20,     8,     9,    10,    20,    16,
      13,    14,    19,    74,    19,    20,    22,    23,    49,    50,
       0,    20,    12,    14,     7,    14,    12,    11,    13,    17,
      11,    18,    11,    57,    16,    33,    12,    12,    16,    12,
      -1,    -1,    19,    14,    12,    11,    18,    21,    18,     9,
      12,    20,     6,    20,    18,    -1,    21,    20
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,    11,    25,    26,    18,    13,    13,
      20,    27,     0,    25,    11,    20,    28,    30,    20,    36,
      37,    12,    28,     8,     9,    10,    13,    14,    35,    14,
       7,    29,    14,    17,     5,     6,    12,    16,    19,    33,
      34,    11,    28,    11,    36,    11,    13,    19,    20,    22,
      23,    27,    27,    27,    11,    20,    31,    32,    16,    16,
      34,    34,    12,    12,    12,    31,    21,    14,    29,    18,
      18,    18,    12,    20,    11,    31,     9,    27,    20,    12,
      21,    18,    20
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    24,    25,    25,    26,    26,    26,    26,    26,    27,
      28,    28,    29,    30,    30,    31,    31,    32,    32,    33,
      33,    33,    34,    34,    34,    35,    35,    35,    35,    35,
      36,    36,    37
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     8,     8,     8,    11,     2,     1,
       3,     1,     1,     3,     3,     3,     1,     3,     7,     1,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       3,     1,     1
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
        case 4:
#line 107 "bison_dbms.y" /* yacc.c:1646  */
    {

            int condition_it = 0;

            // Check syntax
            printf("Valid Syntax \n");

            char filename[50];
            strcpy(filename, (yyvsp[-2].sval));
            strcat(filename, ".csv");
            readcsv(filename);

            FILE *file_in = fopen("intermediate.cpp", "w+");
            insert_header(file_in);

            // Open the file in which table exists
            fprintf(file_in, "\tstring tableName = \"%s\";\n", (yyvsp[-2].sval));
            fprintf(file_in, "\treadcsv(tableName+\".csv\", 0);\n");
            // fprintf(file_in, "\tprintColumnNames();\n");
            // Iterate over each row of table
            fprintf(file_in, "\tprintColumnName(tableName);");
            fprintf(file_in, "\tcout << endl;");

            fprintf(file_in, "\tfor(int j = 0; j < getNumRows(tableName); j++) {\n");

                // Put if condition_str
                fprintf(file_in, "\t\tif (");

                // Iterate over condition and check data type with schema
                for (condition_it = 0; condition_it < condition_ptr; condition_it++) {
                    // Get column name
                    char *columnName = condition[condition_it++];
                    char *operator = condition[condition_it++];
                    char *rhs = condition[condition_it++];

                    // Both number
                    if (gettype((yyvsp[-2].sval), columnName) == NUMBER && isnum(rhs) == TRUE) {
                        fprintf(file_in, "stoi(getVal(0, j, \"%s\")) %s %s ", columnName, operator, rhs);
                    }
                    // Both string
                    else if (gettype((yyvsp[-2].sval), columnName) == STRING && isnum(rhs) == FALSE) {
                        if (!strcmp(operator, "=="))
                            fprintf(file_in, "getVal(0, j, \"%s\") %s %s ", columnName, operator, rhs);
                        else {
                            printf("Operator unsupported for condition %s %s %s", columnName, operator, rhs);
                            exit(0);
                        }    
                    }
                    else {
                        printf("gettype(%s) = %d\n", "name", gettype((yyvsp[-2].sval), "name"));
                        printf("Datatype mismatch in Schema for condition %s %s %s", columnName, operator, rhs);
                        exit(0);
                    }

                    if (condition_it < condition_ptr) {
                        char *and_or_op = condition[condition_it];
                        fprintf(file_in, " %s ", and_or_op);
                    }
                }
                // Put if condition_str
                fprintf(file_in, ") {\n");

                    fprintf(file_in, "\t\t\tprintRow(0, j);\n");

            fprintf(file_in, "\t\t}\n");
            fprintf(file_in, "\t}\n");

            insert_footer(file_in);
            fclose(file_in);
        }
#line 1395 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 177 "bison_dbms.y" /* yacc.c:1646  */
    {
            printf("Valid Syntax \n");
            int i = 0;
            for (i = 0; i < position; i++) {
                printf("%s ,", column[i]);
            }

            FILE *file_in = fopen("intermediate.cpp", "w+");
            insert_header(file_in);

            // Construct vector of columnNames
            fprintf(file_in, "\tvector<string> columnNames;\n");
            
            for (i = 0; i < position; i++) {
                fprintf(file_in, "\tcolumnNames.push_back(\"%s\");\n", column[i]);
            }

            fprintf(file_in, "\tprintColumns(columnNames);\n");

            insert_footer(file_in);
            fclose(file_in);
        }
#line 1422 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 199 "bison_dbms.y" /* yacc.c:1646  */
    {
           printf("Valid Syntax \n");

            FILE *file_in = fopen("intermediate.cpp", "w+");
            insert_header(file_in);
            fprintf(file_in, "\tint r0 = getNumRows(0);\n");
            fprintf(file_in, "\tint r1 = getNumRows(1);\n");
            fprintf(file_in, "\tfor(int i = 0; i < r0;i++){\n");
            fprintf(file_in, "\t\tstring s = getRow(0, i);\n");
            fprintf(file_in, "\t\tfor(int j = 0; j < r1;j++)\n");
            fprintf(file_in, "\t\t\tcout << s << getRow(0, i) << endl;\n}\n");

            insert_footer(file_in);
            fclose(file_in);
        }
#line 1442 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 214 "bison_dbms.y" /* yacc.c:1646  */
    {
           printf("Valid Syntax \n");

            // Open both tables -> $2 and $9
            // Extract table names from condition_list_eq (len should be 2 and should be equal to both table names)
            // Check column names (should exists in respective tables)
            // Perform calculation

            FILE *file_in = fopen("intermediate.cpp", "w+");
            insert_header(file_in);
            fprintf(file_in, "\tstring tableName1 = \"%s\";\n", (yyvsp[-9].sval));
            fprintf(file_in, "\treadcsv(tableName1+\".csv\", 0);\n");
            fprintf(file_in, "\tstring tableName2 = \"%s\";\n", (yyvsp[-2].sval));
            fprintf(file_in, "\treadcsv(tableName2+\".csv\", 1);\n");

            // Check the table names (should be either $2 or $9)
            int condition_it = 0;
            for (condition_it = 0; condition_it < condition_ptr; condition_it++) {
                char *table1 = condition[condition_it++];
                char *attribute1 = condition[condition_it++];
                char *table2 = condition[condition_it++];
                char *attribute2 = condition[condition_it++];   // After increment, Now at logical operation (and / or)
                
                if (strcmp(table1, (yyvsp[-9].sval)) && strcmp(table1, (yyvsp[-2].sval))) // means none matches
                {
                    printf("Table names not matched in condition : %s\n", table1);
                    exit(0);
                }
                if (strcmp(table2, (yyvsp[-9].sval)) && strcmp(table2, (yyvsp[-2].sval))) // means none matches
                {
                    printf("Table names not matched in condition : %s\n", table2);
                    exit(0);
                }

                // Attribute1 should be in table 1
                char filename[50];
                strcpy(filename, table1);
                strcat(filename, ".csv");
                readcsv(filename);

                if (getcolindex(getfileindex(table1), attribute1) == -1)    // Column doesn't exists in table1
                {
                    printf("Invalid column name : %s in %s\n", attribute1, table1);
                    exit(0);
                }

                strcpy(filename, table2);
                strcat(filename, ".csv");
                readcsv(filename);
                if (getcolindex(getfileindex(table2), attribute2) == -1)    // Column doesn't exists in table2
                {
                    printf("Invalid column name : %s in %s\n", attribute2, table2);
                    exit(0);
                }
            
                // Check data type of attribute 1 from table 1 and attribute 2 from table 2
                if(gettype(table1, attribute1) != gettype(table2, attribute2)) {
                    printf("Data type mismatch column names : %s and %s\n", attribute1, attribute2);
                }
            }

            fprintf(file_in, "\tprintColumnName(tableName1);");
            fprintf(file_in, "\tcout << \" \";");
            fprintf(file_in, "\tprintColumnName(tableName2);");
            fprintf(file_in, "\tcout << endl;");

            // Iterate over each row of table
            fprintf(file_in, "\tfor(int j1 = 0; j1 < getNumRows(tableName1); j1++) {\n");
            fprintf(file_in, "\t\tfor(int j2 = 0; j2 < getNumRows(tableName2); j2++) {\n");

                // Put if condition_str
                fprintf(file_in, "\t\t\tif (");

                // Iterate over conditions.
                for (condition_it = 0; condition_it < condition_ptr; condition_it++) {
                    // Get column name
                    char *table1 = condition[condition_it++];
                    char *attribute1 = condition[condition_it++];
                    char *table2 = condition[condition_it++];
                    char *attribute2 = condition[condition_it++];   // After increment, Now at logical operation (and / or)                

                    if(!strcmp(table1, (yyvsp[-9].sval))){
                        fprintf(file_in, "getVal(getindexfortable(\"%s\"), j1, \"%s\") ", table1, attribute1);
                    }
                    else {
                        fprintf(file_in, "getVal(getindexfortable(\"%s\"), j2, \"%s\") ", table1, attribute1);
                    }

                    if(!strcmp(table2, (yyvsp[-2].sval))){
                        fprintf(file_in, "== getVal(getindexfortable(\"%s\"), j2, \"%s\") ", table2, attribute2);
                    }
                    else {
                        fprintf(file_in, "== getVal(getindexfortable(\"%s\"), j1, \"%s\") ", table2, attribute2);
                    }
                        
                    if (condition_it < condition_ptr) {
                        char *and_or_op = condition[condition_it];
                        fprintf(file_in, " %s ", and_or_op);
                    }
                }
                // Put if condition_str
                fprintf(file_in, ") {\n");

                fprintf(file_in, "\t\t\tstring r1 = getRow(getindexfortable(tableName1), j1);\n");
                fprintf(file_in, "\t\t\tstring r2 = getRow(getindexfortable(tableName2), j2);\n");
                fprintf(file_in, "\t\t\tcout << r1 << \" \" << r2 << \"\\n\";" );

            fprintf(file_in, "\t\t\t}\n");
            fprintf(file_in, "\t\t}\n");
            fprintf(file_in, "\t}\n");

            insert_footer(file_in);
            fclose(file_in);

        }
#line 1562 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 329 "bison_dbms.y" /* yacc.c:1646  */
    {
           yyerrok;
           eat_till_semi();
        }
#line 1571 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 336 "bison_dbms.y" /* yacc.c:1646  */
    { 
                    strcat((yyval.sval), " "); 
                    strcat((yyval.sval), (yyvsp[-1].sval)); 
                    strcat((yyval.sval), " "); 
                    strcat((yyval.sval), (yyvsp[0].sval)); 
                }
#line 1582 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 344 "bison_dbms.y" /* yacc.c:1646  */
    {
                    strcpy(condition[condition_ptr++], (yyvsp[0].sval));
                }
#line 1590 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 349 "bison_dbms.y" /* yacc.c:1646  */
    { strcat((yyval.sval), " "); strcat((yyval.sval), (yyvsp[-1].sval)); strcat((yyval.sval), " "); strcat((yyval.sval), (yyvsp[0].sval)); }
#line 1596 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 350 "bison_dbms.y" /* yacc.c:1646  */
    { 
                    strcpy(condition[condition_ptr++], (yyvsp[-2].sval));
                    strcpy(condition[condition_ptr++], (yyvsp[-1].sval));
                    strcpy(condition[condition_ptr++], (yyvsp[0].sval));
                    }
#line 1606 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 360 "bison_dbms.y" /* yacc.c:1646  */
    {
                    strcpy(condition[condition_ptr++], (yyvsp[-6].sval));
                    strcpy(condition[condition_ptr++], (yyvsp[-4].sval));
                    strcpy(condition[condition_ptr++], (yyvsp[-2].sval));
                    strcpy(condition[condition_ptr++], (yyvsp[0].sval));
                    }
#line 1617 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 368 "bison_dbms.y" /* yacc.c:1646  */
    { strcat((yyval.sval), (yyvsp[-1].sval)); strcat((yyval.sval), (yyvsp[0].sval)); strcat((yyval.sval), " "); }
#line 1623 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 369 "bison_dbms.y" /* yacc.c:1646  */
    { strcat((yyval.sval), (yyvsp[-1].sval)); strcat((yyval.sval), (yyvsp[0].sval)); strcat((yyval.sval), " "); }
#line 1629 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 371 "bison_dbms.y" /* yacc.c:1646  */
    { strcat((yyval.sval), " "); strcat((yyval.sval), (yyvsp[-1].sval)); strcat((yyval.sval), " "); strcat((yyval.sval), (yyvsp[0].sval)); }
#line 1635 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 372 "bison_dbms.y" /* yacc.c:1646  */
    { strcat((yyval.sval), " "); strcat((yyval.sval), (yyvsp[-1].sval)); strcat((yyval.sval), " "); strcat((yyval.sval), (yyvsp[0].sval)); }
#line 1641 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 375 "bison_dbms.y" /* yacc.c:1646  */
    { strcat((yyval.sval), (yyvsp[0].sval)); }
#line 1647 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 384 "bison_dbms.y" /* yacc.c:1646  */
    {
        strcpy(column[position], (yyvsp[0].sval));
        position++;
    }
#line 1656 "bison_dbms.tab.c" /* yacc.c:1646  */
    break;


#line 1660 "bison_dbms.tab.c" /* yacc.c:1646  */
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
#line 388 "bison_dbms.y" /* yacc.c:1906  */


int main(int argc, char **argv) {

    char *filename = "tests/test1.txt";
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
  
}

void yyerror(const char *s) {
  print("Invalid syntax ", s);
  // might as well halt now:
//   printf("Invalid Syntax\n");
//   exit(-1);
}

void eat_till_semi()
{
    int c;
    while((c = (char)fgetc(yyin)) != EOF && c != ';')
        printf("s");
}

void insert_header (FILE *filename) {
    FILE *fp = fopen("readcsv.cpp", "r");
    int c;
    while((c = (char)fgetc(fp)) != EOF)
        fprintf(filename, "%c", (char)c);
    fclose(fp);

    fprintf(filename, "\nint main () {\n");
}

void insert_footer (FILE *filename) {
    char *header = "return 0;\n}\n";

    fprintf(filename, "%s", header);
}

void extract_column(char *table) {
    // Get the Schema and column name from the table
    // Assuming schema in 1st row and column name in 2nd row
    FILE *f_in = fopen(strcat(table, ".txt"), "r");

    fgets(schema, sizeof(schema), f_in);
    fgets(column_str, sizeof(column_str), f_in);
    printf("%s\n", schema);
    printf("%s\n", column_str);
    
    // Extract column name from column_str
    int i = 0;
    int begin = 0;
    int end = -1;
    int j = 0;
    int k = 0;
    for (i = 0; i < strlen(column_str); i++) {
        if (column_str[i] == ',') {
            end = i;
            for (k = begin; k < end; k++) {
                column[j][k-begin] = column_str[k];
            }
            column[j][k-begin] = '\0';
            j++;
            begin = i+1;
        }
    }
    num_column = j;
}

void readcsv(char* name)
{
    int index = num_files;
	//name of the file pushed
	int name_len = strlen(name);
	for (int i = 0; i < name_len-4; ++i)
	{
		file_name[index][i] = name[i];
	}

	FILE* stream = fopen(name, "r");
	char type_line[1024];
	int itr;
	
	if(fgets(type_line, 1024, stream))
	{
        int len = strlen(type_line);
   		// printf("%s\n", type_line);
   		int i=0;
	}

	char name_line[1024];
	if(fgets(name_line, 1024, stream))
	{
   		// printf("%s\n", name_line);
   		int i=0;
	}


	int top=0;
    int len = strlen(name_line);
    int j=0;
	for (int i = 0; i < len; ++i)
	{
		if(name_line[i] != ',' && name_line[i] != '\n')
		{
			col_name[index][top][j++] = name_line[i];
		}
		else
		{
			j = 0;
			top++;
		}	
	}
		
	top = 0;
    len = strlen(type_line);
    for (int i = 0; i < len; ++i)
	{
		if(type_line[i] != ',' && type_line[i] != '\n')
		{
			data_type[index][top] = type_line[i];
		}
		else
		{
			top++;
		}	
	}
	num_files++;
}

int getfileindex(char* name)
{
    // printf ("name = *%s*\n", name);
	for (int i = 0; i < MAX_FILES; ++i)
	{
		if(strcmp(file_name[i], name)==0)
		{
            // printf ("filenames = *%s*\n", file_name[i]); 
			return i;
		}
	}
	return -1;
}

int getcolindex(int index, char* col)
{
	for (int i = 0; i < MAX_COLS; ++i)
	{
		if(strcmp(col_name[index][i], col) == 0)
		{
			return i;
		}
	}
	return -1;
}

//returns 0 for string 1 for int
int gettype(char* table_name, char* col)
{
	int index = getfileindex(table_name);
	if(index == -1)
	{
		printf("No such Table loaded.\n");
		return -1;
	}

	int colindex = getcolindex(index, col);
	if(colindex == -1)
	{
        // printf("Here is the problem\n");
        printf("column name = %s\n", col);
		printf("No such column exists.\n");
		exit(0);
	}	

	if(data_type[index][colindex] == 'i')
	{
		return 1;
	}
	return 0;
}

int isnum (char *text) {
    int i = 0;
    if (text[0] == '"')
        return 0;
    else
        return 1;
}
