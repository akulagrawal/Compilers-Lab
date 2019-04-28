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
    #define SIZE_INT 4
    #define SIZE_FLOAT 4
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

        void insert_parameter(string parameter_name, string type, int level = 1){
            parameters.push_back(var_record(parameter_name, type, true, level));
        }

        void insert_variable(string var_name, string type, int level = 2){
            local_variables.push_back(var_record(var_name, type, false, level));
        }

        bool search_param(string parameter_name, var_record *&r) {
            for(auto it = parameters.begin(); it != parameters.end(); ++it){
                if(it -> name == parameter_name){
                    r = &(*it);
                    return true;
                }
            }
            return false;
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

        void insert_function(string function_name, string datatype, list<var_record> active_func_param_list) {
            function_record * r = new function_record;
            r -> function_return_type = datatype;

            // Add param_list_declaration to symbol_table corresponding to active function
            for (auto it = active_func_param_list.begin(); it != active_func_param_list.end(); it++) {
                r -> insert_parameter(it->name, it->type, it->level);
            }

            active_func_param_list.clear();
            entries[function_name] = *r;
        }

        bool search_function(string function_name, function_record *&function) {
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

    /* Intermediate Code Generation. */
    /* Quadruples. */
    struct quadruple {
        string _operator;
        string _arg1;
        string _arg2;
        string _result;

        quadruple() {}

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
    int glob_temp = 0;
    map<string, int> func_temps;
    string get_next_temp(string func_name = ""){
        if(func_name == ""){
            glob_temp += 1;
            return "t" + std::to_string(glob_temp);
        } else {
            func_temps[func_name] += 1;
            return "t" + func_name + std::to_string(func_temps[func_name]);
        }
    }

    /* abhishek */
    bool isNumber(const string &line)
	{
		if (line[0] == '0') return true;
		return (atoi(line.c_str()));
	}

	class variable{
		public:
		string name;
		string type;
		string value;
        string function_name;
        int level;

		bool isarray;
		int startoffset;
		int endoffset;
        int quadindex; // the quadruple for declaration
		vector<string> dimension;

		variable(string v_name, string v_type, string v_value, bool v_isarray, vector<string> v_dimension, string v_func_name = "", int v_level = 0){
			this->name = v_name;
			this->type = v_type;
			this->value = v_value;
			this->isarray = v_isarray;
			this->dimension = v_dimension;
			this->startoffset = 0;
			this->endoffset = -1;
            this->function_name = v_func_name;
            this->level = v_level;
		}

	};

	class ab_symbol_table{
		public:
		vector <variable> tab;

		void insertintosymtab(variable v, int index){

			if(tab.size() == 0)
				v.startoffset = 0;
			else
				v.startoffset = tab[tab.size()-1].endoffset;

			long long int mul = 1;
			for (int i = 0; i < v.dimension.size(); ++i){
				if(isNumber(v.dimension[i])){
					mul *= stoi(v.dimension[i]);
				}
				else{
					mul *= stoi(tab[this->search(v.dimension[i])].value);
				}
			}

			if(v.type == "i")
				mul *= SIZE_INT;
			else
				mul *= SIZE_FLOAT;

			v.endoffset = v.startoffset + mul;
            v.quadindex = index;
			tab.push_back(v);
		}

		void printsymtab()	{
			cout<<"Symbol Table: "<<endl;
			for(int i=0;i<this->tab.size();i++)
			{
				cout<<"Start: "<<this->tab[i].startoffset<<endl;
				cout<<this->tab[i].name<<": "<<this->tab[i].value<<" ( "<<this->tab[i].type<<" )";
				if(this->tab[i].isarray)
				{
					cout<<" Dim: ";
					for (int j = 0; j < this->tab[i].dimension.size(); ++j)
					{
						cout<<", "<<this->tab[i].dimension[j];
					}
				}
				cout<<endl;
			}
		}

		vector <string> getvarvector(char* s){
			vector<string> ans;
			string var_name = "";
			char* itr = s;
			while(*itr){
				if(*itr == ','){
					ans.push_back(var_name);
					var_name = "";
					itr++;
					continue;
				}
				var_name += *itr;
				itr++;
			}
			if(var_name != ""){
				ans.push_back(var_name);
			}
			return ans;
		}

		void patch(char* v_type, char* s){
			vector<string> var_names = this->getvarvector(s);
			for (int i = 0; i < var_names.size(); ++i){

				for (int j = 0; j < tab.size(); ++j){
					if(tab[j].name == var_names[i]){
						tab[j].type = strdup(v_type);
                        quadruples[tab[j].quadindex]._arg1 = string(tab[j].type);
						break;
					}
				}
			}
		}

		int search(string varname){
			for (int i = 0; i < tab.size(); ++i){
				if(tab[i].name == varname)
					return i;
			}
			return -1;
		}

        bool search_var(string varname, int &cur_level, string functionName, string &datatype) {
            vector<int> position;
            for (int i = 0; i < tab.size(); ++i) {
                if (tab[i].name == varname && tab[i].function_name == functionName)
                    position.push_back(i);
                else if (tab[i].name == varname && tab[i].function_name == "")
                    position.push_back(i);
            }
            if (position.empty()) {
                return false;
            }
            else {
                int pos_with_max_level = 0;
                int max_level = 0;
                for (int i = 0; i < position.size(); i++) {
                    if (tab[position[i]].level > max_level) {
                        pos_with_max_level = position[i];
                        max_level = tab[position[i]].level;
                    }
                }
                cur_level = max_level;
                datatype = tab[pos_with_max_level].type;
            }
            return true;
        }

        void delete_var_from_level(string function_name, int level) {
            for (auto it = tab.begin(); it != tab.end(); ) {
                if (it->function_name == function_name && it->level == level) {
                    it = tab.erase(it);
                }
                else
                    it++;
            }
        }
	};

	ab_symbol_table ab_symtab = ab_symbol_table();
	vector<string> dummy;

	vector <string> makedimlist(char* s){
		vector<string> ans;
		string var_name = "";
		char* itr = s;
		while(*itr){
			if(*itr == ','){
				ans.push_back(var_name);
				var_name = "";
				itr++;
				continue;
			}
			var_name += *itr;
			itr++;
		}
		if(var_name != ""){
			ans.push_back(var_name);
		}
		return ans;
	}

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

    // Keep track of whether inside switch case statement
    int insideSwitchCase = 0;
    // Keep track of whether inside loops
    int insideLoop = 0;

    extern bool isInt(const char *type);
    extern bool isFloat(const char *type);
    extern bool isBoolean(const char *type);
    extern bool isErrorType(const char *type);
    extern bool isVoidType(const char *type);
    extern bool isMatch(const char *str1, const char *str2);
    extern void set_active_function(const char *str);
    extern char* setVoidType();

    extern bool isInt(string type);
    extern bool isFloat(string type);
    extern bool isBoolean(string type);
    extern bool isErrorType(string type);
    extern bool isVoidType(string type);
    extern bool isMatch(string str1, string str2);
    extern void set_active_function(string str);

    extern bool isInsideFunc();
    extern char* setErrorType();
    extern char* setIntType();
    extern char* setNoErrorType();
    extern void reset_active_function();
    extern void errorLine(string errorMsg);
    extern void warning(string warningMsg);
    extern bool isVariableInSymtab(string varname);
    extern bool checkForVariable(string var_name, string &datatype, string active_func, int cur_level, bool flag);
    extern void delete_var_list(string function_name, int level);
    extern bool isCompatible(string type1, string type2);
    extern string Variable(string str);

#line 437 "c_lang.tab.c" /* yacc.c:339  */

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
    AND = 263,
    REL_OP = 264,
    IF = 265,
    ELSE = 266,
    FOR = 267,
    WHILE = 268,
    SWITCH = 269,
    CASE = 270,
    DEFAULT = 271,
    BREAK = 272,
    CONTINUE = 273,
    RETURN = 274
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 372 "c_lang.y" /* yacc.c:355  */

    struct {
        struct indexlist * indexlist;
        char* type;
        int val;
        int index;
        int len;
        char* sval;
    } type_id;

#line 508 "c_lang.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_LANG_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 525 "c_lang.tab.c" /* yacc.c:358  */

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   180

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  149

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   274

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
      22,    23,    30,    28,    24,    29,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,    25,
       2,    27,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    20,     2,    21,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   419,   419,   420,   421,   422,   426,   448,   457,   464,
     464,   485,   485,   506,   528,   554,   576,   587,   591,   625,
     684,   694,   718,   722,   726,   731,   736,   740,   759,   766,
     776,   789,   796,   809,   809,   823,   845,   853,   890,   927,
     969,   985,  1002,  1002,  1013,  1020,  1025,  1025,  1035,  1040,
    1051,  1056,  1067,  1073,  1081,  1087,  1093,  1099,  1108,  1139,
    1151,  1158,  1168,  1179,  1187,  1195,  1204,  1212,  1220,  1229,
    1237,  1251,  1256,  1271,  1283,  1288,  1298,  1313,  1327,  1345,
    1356
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "IDENTIFIER", "TYPE", "VOID",
  "OR", "AND", "REL_OP", "IF", "ELSE", "FOR", "WHILE", "SWITCH", "CASE",
  "DEFAULT", "BREAK", "CONTINUE", "RETURN", "'{'", "'}'", "'('", "')'",
  "','", "';'", "':'", "'='", "'+'", "'-'", "'*'", "'/'", "'['", "']'",
  "$accept", "START", "function_declaration", "function_result_assignment",
  "function_head", "$@1", "$@2", "param_list_declaration",
  "param_declaration", "function_call", "arg_list", "statement",
  "conditional_statement", "$@3", "if_exp", "else_mark", "loop_statement",
  "FOREXP", "WHILEEXP", "labeled_statement", "$@4", "compound_statement",
  "$@5", "statement_list", "expression_statement", "expression_cover",
  "expression", "assignment_expression", "logical_expression",
  "logical_operation", "relational_expression", "arithmetic_expression",
  "arithmetic_term", "arithmetic_factor", "variable_declaration_statement",
  "name_list", "id_arr", "bracket_dimlist", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     123,   125,    40,    41,    44,    59,    58,    61,    43,    45,
      42,    47,    91,    93
};
# endif

#define YYPACT_NINF -54

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-54)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      77,     1,    11,    32,   -54,    -3,   -54,    13,    22,    30,
      35,   -54,   -54,   -54,    42,    51,    86,    74,   -54,   -54,
      80,    68,   -54,   109,   -54,   106,   -54,    93,    86,   -54,
     -54,    81,    75,    85,    28,   -54,   -54,   106,    43,    80,
     108,   131,   134,   137,   148,   128,   136,   138,    26,   139,
     113,   -54,   -54,   -54,   109,   -54,    46,   109,   -54,   -54,
       6,   -54,    72,   140,   -54,   -54,   -54,   -54,   -54,   153,
     122,   -54,    49,   141,    86,    86,    86,    86,   130,   124,
      86,   113,    26,   113,   113,   142,   109,   -54,   -54,   -54,
     -54,   109,   129,   -54,   141,   155,   109,   144,   -54,   -54,
     -54,   -54,   -54,   113,   113,   -54,   -54,   -54,   106,   -54,
     126,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,
     132,    26,   135,   146,   -54,   -54,    82,   -54,   -54,   109,
     -54,   109,    72,    72,   -54,   -54,    86,   -54,   -54,   -54,
     -54,   109,   -54,   -54,   -54,   -54,   109,   -54,   -54
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     0,     3,    76,     0,    74,
       0,     1,     4,     5,     8,     9,     0,     0,    78,    73,
       0,    11,     7,     0,    13,     0,    71,    70,     0,    72,
      77,    65,    68,     0,    76,    75,    14,     0,    70,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
       0,    50,    48,    22,     0,    23,     0,     0,    28,    24,
       0,    25,     0,    52,    54,    55,    56,    57,    26,     0,
       0,    16,     0,     0,     0,     0,     0,     0,    79,     0,
       0,     0,     0,     0,     0,     0,     0,    29,    30,    27,
      45,     0,     0,    52,    57,    31,     0,    52,    37,     6,
      49,    60,    61,     0,     0,    51,    17,    10,     0,    18,
       0,    20,    69,    63,    64,    66,    67,    80,    12,    58,
       0,     0,     0,    52,    42,    44,     0,    53,    36,     0,
      38,     0,    62,    59,    15,    19,     0,    35,    40,    41,
      33,     0,    47,    32,    39,    21,     0,    43,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -54,   -54,   167,   -54,   -54,   -54,   -54,   143,    63,   -54,
     -54,   -53,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,
     -54,   -54,   -54,    83,   -46,   -37,   -42,   -54,   -54,   -54,
     -54,   -16,    56,   -54,     3,   152,   -54,    95
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    23,     5,    25,    37,    70,    71,    29,
     110,    52,    53,   146,    54,   129,    55,    56,    57,    58,
     141,    59,    91,    60,    61,    62,    63,    64,    65,   104,
      66,    67,    31,    32,    68,     8,     9,    18
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      30,    95,    89,     6,    98,     7,    13,   100,    93,    26,
      38,    39,    73,    92,    97,    10,    40,    14,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    99,    50,    26,
      38,    51,    11,   125,    94,    15,   121,     1,     2,    93,
      16,    93,   123,   130,   120,    17,   122,    19,    50,    26,
      38,    51,    26,    27,    20,    16,   111,    21,   113,   114,
      17,    93,    93,    22,   119,    72,   132,   133,    50,    96,
      80,    28,   109,   100,    24,   138,   143,    33,   144,   101,
     102,   103,     1,     2,    34,    26,    38,    39,   147,    26,
      27,    36,    40,   148,    41,    42,    43,    44,    45,    46,
      47,    48,    49,   142,    50,    76,    77,    51,    28,    74,
      75,    69,    26,    38,    39,    72,    26,    38,    78,    40,
     145,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      81,    50,   115,   116,    51,    50,   101,   102,   103,   101,
     102,   103,   101,   102,   103,   107,   108,   118,   108,   135,
     136,    85,   127,    82,    86,   137,    83,   106,   139,    84,
      90,    87,    17,    88,   112,   105,   128,   131,   124,   140,
      12,   134,    35,   117,   126,     0,     0,     0,     0,     0,
      79
};

static const yytype_int16 yycheck[] =
{
      16,    54,    48,     0,    57,     4,     3,    60,    50,     3,
       4,     5,    28,    50,    56,     4,    10,    20,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     3,
       4,    25,     0,    86,    50,    22,    82,     5,     6,    81,
      27,    83,    84,    96,    81,    32,    83,    25,    22,     3,
       4,    25,     3,     4,    24,    27,    72,    22,    74,    75,
      32,   103,   104,    21,    80,    22,   103,   104,    22,    23,
      27,    22,    23,   126,    23,   121,   129,     3,   131,     7,
       8,     9,     5,     6,     4,     3,     4,     5,   141,     3,
       4,    23,    10,   146,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    30,    31,    25,    22,    28,
      29,     5,     3,     4,     5,    22,     3,     4,    33,    10,
     136,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      22,    22,    76,    77,    25,    22,     7,     8,     9,     7,
       8,     9,     7,     8,     9,    23,    24,    23,    24,    23,
      24,     3,    23,    22,    26,    23,    22,     4,    23,    22,
      21,    25,    32,    25,    23,    25,    11,    23,    26,    23,
       3,   108,    20,    78,    91,    -1,    -1,    -1,    -1,    -1,
      37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    35,    36,    38,    68,     4,    69,    70,
       4,     0,    36,    68,    20,    22,    27,    32,    71,    25,
      24,    22,    21,    37,    23,    39,     3,     4,    22,    43,
      65,    66,    67,     3,     4,    69,    23,    40,     4,     5,
      10,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      22,    25,    45,    46,    48,    50,    51,    52,    53,    55,
      57,    58,    59,    60,    61,    62,    64,    65,    68,     5,
      41,    42,    22,    65,    28,    29,    30,    31,    33,    41,
      27,    22,    22,    22,    22,     3,    26,    25,    25,    58,
      21,    56,    59,    60,    65,    45,    23,    60,    45,    21,
      45,     7,     8,     9,    63,    25,     4,    23,    24,    23,
      44,    65,    23,    65,    65,    66,    66,    71,    23,    65,
      59,    58,    59,    60,    26,    45,    57,    23,    11,    49,
      45,    23,    59,    59,    42,    23,    24,    23,    58,    23,
      23,    54,    21,    45,    45,    65,    47,    45,    45
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    35,    35,    35,    36,    36,    37,    39,
      38,    40,    38,    38,    38,    41,    41,    42,    43,    43,
      44,    44,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    46,    46,    47,    46,    48,    49,    50,    50,    50,
      51,    52,    54,    53,    53,    55,    56,    55,    57,    57,
      58,    58,    59,    59,    60,    60,    60,    60,    61,    62,
      63,    63,    64,    65,    65,    65,    66,    66,    66,    67,
      67,    67,    67,    68,    69,    69,    70,    70,    70,    71,
      71
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     5,     3,     0,     0,
       6,     0,     6,     4,     4,     3,     1,     2,     3,     4,
       1,     3,     1,     1,     1,     1,     1,     2,     1,     2,
       2,     2,     4,     0,     6,     4,     1,     2,     3,     4,
       4,     4,     0,     5,     3,     2,     0,     4,     1,     2,
       1,     2,     1,     3,     1,     1,     1,     1,     3,     3,
       1,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     1,     1,     3,     1,     3,     1,     3,     2,     3,
       4
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
#line 427 "c_lang.y" /* yacc.c:1646  */
    {
        // get a variable assigned to this function to be returned.
        string temp = "t" + string((yyvsp[-4].type_id).sval);

        // update type of this variable.
        quadruples[(yyvsp[-2].type_id).index]._arg1 = (yyvsp[-4].type_id).type;

        // update quads with (funcvar) which need to be filled in.
        for(int index = (yyvsp[-2].type_id).index; index < quadruples.size(); ++index){
            if(quadruples[index]._result == "(funcvar)"){
                quadruples[index]._result = temp;
            }
        }

        quadruples.push_back(quadruple("end", string((yyvsp[-4].type_id).sval), "", ""));

        delete_var_list(active_func_name, level);
        level --;
        reset_active_function();
        level --;
    }
#line 1735 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 449 "c_lang.y" /* yacc.c:1646  */
    {
        delete_var_list(active_func_name, level);
        level--;
        reset_active_function();
    }
#line 1745 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 458 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).index = quadruples.size();
        quadruples.push_back(quadruple("assign", "(type)", "1", "(funcvar)"));
    }
#line 1754 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 464 "c_lang.y" /* yacc.c:1646  */
    { level ++; }
#line 1760 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 465 "c_lang.y" /* yacc.c:1646  */
    {
        quadruples.push_back(quadruple("label", string((yyvsp[-4].type_id).sval), to_string((yyvsp[-1].type_id).len), ""));

        level ++;
        function_record *r;

        // Check if function already exists
        if (symtab.search_function((yyvsp[-4].type_id).sval, r)) {
            errorLine("Redeclaration of function '" + Variable(string((yyvsp[-4].type_id).sval)) + "'");
            r->function_return_type = setErrorType();
            (yyval.type_id).type = setErrorType();
        }
        else {
            symtab.insert_function((yyvsp[-4].type_id).sval, (yyvsp[-5].type_id).sval, active_func_param_list);
            (yyval.type_id).type = strdup((yyvsp[-5].type_id).sval);
        }

        (yyval.type_id).sval = (yyvsp[-4].type_id).sval;
        set_active_function((yyvsp[-4].type_id).sval);
    }
#line 1785 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 485 "c_lang.y" /* yacc.c:1646  */
    { level ++; }
#line 1791 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 486 "c_lang.y" /* yacc.c:1646  */
    {
        quadruples.push_back(quadruple("label", string((yyvsp[-4].type_id).sval), to_string((yyvsp[-1].type_id).len), ""));

        level ++;
        function_record *r;

        // Check if function already exists
        if (symtab.search_function((yyvsp[-4].type_id).sval, r)) {
            errorLine("Redeclaration of function '" + Variable(string((yyvsp[-4].type_id).sval)) + "'");
            r->function_return_type = setErrorType();
            (yyval.type_id).type = setErrorType();
        }
        else {
            symtab.insert_function((yyvsp[-4].type_id).sval, (yyvsp[-5].type_id).sval, active_func_param_list);
            (yyval.type_id).type = strdup((yyvsp[-5].type_id).sval);
        }

        (yyval.type_id).sval = (yyvsp[-4].type_id).sval;
        set_active_function((yyvsp[-4].type_id).sval);
    }
#line 1816 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 507 "c_lang.y" /* yacc.c:1646  */
    {
        quadruples.push_back(quadruple("label", string((yyvsp[-2].type_id).sval), to_string(0), ""));

        level += 2;
        function_record *r;

        active_func_param_list.clear();

        // Check if function already exists
        if (symtab.search_function((yyvsp[-2].type_id).sval, r)) {
            errorLine("Redeclaration of function '" + Variable(string((yyvsp[-2].type_id).sval)) + "'");
            (yyval.type_id).type = setErrorType();
        }
        else {
            symtab.insert_function((yyvsp[-2].type_id).sval, (yyvsp[-3].type_id).sval, active_func_param_list);
            (yyval.type_id).type = strdup((yyvsp[-3].type_id).sval);
        }

        (yyval.type_id).sval = (yyvsp[-2].type_id).sval;
        set_active_function((yyvsp[-2].type_id).sval);
    }
#line 1842 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 529 "c_lang.y" /* yacc.c:1646  */
    {
        quadruples.push_back(quadruple("label", string((yyvsp[-2].type_id).sval), to_string(0), ""));

        level += 2;
        function_record *r;

        active_func_param_list.clear();

        // Check if function already exists
        if (symtab.search_function((yyvsp[-2].type_id).sval, r)) {
            errorLine("Redeclaration of function '" + Variable(string((yyvsp[-2].type_id).sval)) + "'");
            (yyval.type_id).type = setErrorType();
        }
        else {
            active_func_param_list.clear();
            symtab.insert_function((yyvsp[-2].type_id).sval, (yyvsp[-3].type_id).sval, active_func_param_list);
            (yyval.type_id).type = strdup((yyvsp[-3].type_id).sval);
        }

        (yyval.type_id).sval = (yyvsp[-2].type_id).sval;
        set_active_function((yyvsp[-2].type_id).sval);
    }
#line 1869 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 555 "c_lang.y" /* yacc.c:1646  */
    {
        bool found = false;
        // Check if variable is repeated in parameter list
        for (auto it = active_func_param_list.begin(); it != active_func_param_list.end(); it++) {
            if (it -> name == (yyvsp[0].type_id).sval) {
                errorLine("Redeclaration of parameter '" + Variable(string((yyvsp[0].type_id).sval)) + "'");
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
#line 1895 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 577 "c_lang.y" /* yacc.c:1646  */
    {
        active_func_param_list.clear();
        (yyval.type_id).len = 1;
        var_record param((yyvsp[0].type_id).sval, (yyvsp[0].type_id).type, /* is_parameter = */ true, level) ;
        active_func_param_list.push_back(param);
        (yyval.type_id).type = setNoErrorType();
    }
#line 1907 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 587 "c_lang.y" /* yacc.c:1646  */
    { (yyval.type_id).type = (yyvsp[-1].type_id).sval; (yyval.type_id).sval = (yyvsp[0].type_id).sval; }
#line 1913 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 592 "c_lang.y" /* yacc.c:1646  */
    {
        function_record *r;
        string functionName = (yyvsp[-2].type_id).sval;
        (yyval.type_id).val = 0;

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
                    errorLine("Too few arguments to function '" + Variable(string(functionName)) + "'");
                    (yyval.type_id).type = strdup(r->function_return_type.c_str());
                }

                quadruples.push_back(quadruple("call", (yyvsp[-2].type_id).sval, "", ""));
                (yyval.type_id).val += 1;
            }
            else
                (yyval.type_id).type = setErrorType();
        }
        else {
            // Function not found
            errorLine("Function '" + Variable(string(functionName)) + "' is not declared");
            (yyval.type_id).type = setErrorType();
        }
    }
#line 1951 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 626 "c_lang.y" /* yacc.c:1646  */
    {
        function_record *r;
        string functionName = (yyvsp[-3].type_id).sval;
        (yyval.type_id).val = (yyvsp[-1].type_id).val;

        // search for function declaration
        if (symtab.search_function(functionName, r)) {

            // If function's return type is ErrorType
            if (!isErrorType(r->function_return_type)) {

                (yyval.type_id).type = strdup(r->function_return_type.c_str());
                // Check if param_list_declaration matches with arg_list
                if (r->parameters.size() > (yyvsp[-1].type_id).len) {
                    errorLine("Too few arguments to function '" + Variable(functionName) + "'");
                }
                else if (r->parameters.size() < (yyvsp[-1].type_id).len) {
                    errorLine("Too many arguments to function '" + Variable(functionName) + "'");
                }
                else {
                    // Match the datatypes of param_list_declaration and arg_list
                    auto param_it = r->parameters.rbegin();
                    auto arg_it = called_arg_list.rbegin();
                    while (param_it != r->parameters.rend()) {

                        if (!isMatch(param_it->type, arg_it->type)) {
                            errorLine("datatype mismatch for calling function '" + Variable(functionName) + "'");
                            break;
                        }

                        quadruples.push_back(quadruple("push", arg_it -> name, (yyvsp[-3].type_id).sval, param_it -> name));
                        (yyval.type_id).val += 1;

                        param_it ++;
                        arg_it ++;
                    }

                    auto delete_it = called_arg_list.begin();
                    advance(delete_it, called_arg_list.size() - (yyvsp[-1].type_id).len);

                    called_arg_list.erase(delete_it, called_arg_list.end());

                    quadruples.push_back(quadruple("call", (yyvsp[-3].type_id).sval, "", ""));
                    (yyval.type_id).val += 1;
                }
            }
            else
                (yyval.type_id).type = setErrorType();
        }
        else {
            // Function not found
            errorLine("Function '" + Variable(functionName) + "' is not declared");
            (yyval.type_id).type = setErrorType();
        }
    }
#line 2011 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 685 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).len = 1;
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).type = setNoErrorType();
        string datatype = (yyvsp[0].type_id).type;

        var_record arg((yyvsp[0].type_id).sval, datatype, false, level) ;
        called_arg_list.push_back(arg);
    }
#line 2025 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 695 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val;
        string datatype = (yyvsp[0].type_id).type;
        (yyval.type_id).type = setNoErrorType();

        var_record arg((yyvsp[0].type_id).sval, datatype, /* is_parameter = */ false, level) ;

        called_arg_list.push_back(arg);
        (yyval.type_id).len = (yyvsp[-2].type_id).len + 1;

        // cout << "Called args are: ";
        // for(auto it = called_arg_list.begin(); it != called_arg_list.end(); ++it){
        //     cout << it -> name << " ";
        // }
        // cout << "\n";

        if (isErrorType((yyvsp[-2].type_id).type)) {
            (yyval.type_id).type = setErrorType();
        }
    }
#line 2050 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 719 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2058 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 723 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2066 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 727 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
        (yyval.type_id).val = (yyvsp[0].type_id).val;
    }
#line 2075 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 732 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = setVoidType();
        (yyval.type_id).val = (yyvsp[0].type_id).val;
    }
#line 2084 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 737 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = setVoidType();
    }
#line 2092 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 741 "c_lang.y" /* yacc.c:1646  */
    {
        if (isInsideFunc()){
            (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
            (yyval.type_id).index = quadruples.size();
            (yyval.type_id).val = 1;

            function_record *func;
            symtab.search_function(active_func_name, func);

            if (!isMatch(func->function_return_type, (yyvsp[0].type_id).type))
                warning("'return' with a value '" + string((yyvsp[0].type_id).type) + "', in function returning '" + string(func->function_return_type) + "'");

            quadruples.push_back(quadruple("=", string((yyvsp[0].type_id).sval), "", "(funcvar)"));
        }
        else {
            errorLine("Return out of function scope");
        }
    }
#line 2115 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 760 "c_lang.y" /* yacc.c:1646  */
    {
        if (!insideSwitchCase)
            errorLine("Label conditions not inside switch statement");

        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2126 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 767 "c_lang.y" /* yacc.c:1646  */
    {
        /* Check if inside loop or switch. (to be done). */
        if (!insideLoop && !insideSwitchCase) {
            errorLine("break not inside loop or switch");
        }
        (yyval.type_id).index= quadruples.size();
        (yyval.type_id).val=1;
        quadruples.push_back(quadruple("jmp", "", "", "(loopend)"));
    }
#line 2140 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 777 "c_lang.y" /* yacc.c:1646  */
    {
        /* Check if inside loop or switch. (to be done). */
        if (!insideLoop) {
            errorLine("continue not inside loop.");
        }
        (yyval.type_id).val=1;
        (yyval.type_id).index = quadruples.size();
        quadruples.push_back(quadruple("jmp", "", "", "(loopstart)"));
    }
#line 2154 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 790 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val;
        int gotoindex = (yyvsp[-1].type_id).index;
        quadruples[gotoindex]._result = to_string(gotoindex + (yyvsp[0].type_id).val + 1);
        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2165 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 797 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-3].type_id).val + (yyvsp[-2].type_id).val + (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val;
        int gotoindex1 = (yyvsp[-3].type_id).index;
        quadruples[gotoindex1]._result = to_string(gotoindex1 + (yyvsp[-2].type_id).val + (yyvsp[-1].type_id).val + 1);
        int gotoindex2 = (yyvsp[-1].type_id).index;
        quadruples[gotoindex2]._result = to_string(gotoindex2 + (yyvsp[0].type_id).val + 1);

        if ( !isVoidType((yyvsp[-2].type_id).type) )
            (yyval.type_id).type = strdup((yyvsp[-2].type_id).type);
        else
            (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2182 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 809 "c_lang.y" /* yacc.c:1646  */
    { level ++; insideSwitchCase ++; }
#line 2188 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 810 "c_lang.y" /* yacc.c:1646  */
    {
        delete_var_list(active_func_name, level);
        level --;

        if ( !isInt((yyvsp[-3].type_id).type) && !isFloat((yyvsp[-3].type_id).type) )
            errorLine("int expected in expression of if-else");

        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
        insideSwitchCase --;
    }
#line 2203 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 824 "c_lang.y" /* yacc.c:1646  */
    {
        if (!isErrorType((yyvsp[-1].type_id).type)) {
            if ( isInt((yyvsp[-1].type_id).type) || isFloat((yyvsp[-1].type_id).type) ) {
                (yyval.type_id).type = setNoErrorType();
            }
            else {
                errorLine("int expected in expression of if-else");
                (yyval.type_id).type = setErrorType();
            }
        }

        (yyval.type_id).index = quadruples.size() + 1;
        (yyval.type_id).val = (yyvsp[-1].type_id).val + 2;

        quadruples.push_back(quadruple("=", string((yyvsp[-1].type_id).sval), "", "expres"));
        quadruples.push_back(quadruple("ifF", "expres", "", ""));
        // level ++;

    }
#line 2227 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 846 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        (yyval.type_id).index = quadruples.size();
        quadruples.push_back(quadruple("jmp", "", "", ""));
    }
#line 2237 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 854 "c_lang.y" /* yacc.c:1646  */
    {
        delete_var_list(active_func_name, level);
        level --;

        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);

        (yyval.type_id).val = (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val;
        int gotoindex = (yyvsp[-1].type_id).index;
        //  cout<<"$1.index :"<<$1.index<<" $2.val= "<<$2.val<<endl;
        quadruples[gotoindex]._result = to_string(gotoindex + (yyvsp[0].type_id).val + 2);

        for(int i =gotoindex+1;i<gotoindex + (yyvsp[0].type_id).val + 2 && i< quadruples.size();i++ )
        {
        //string s=jmp;
        if(quadruples[i]._operator=="jmp")
        {
            quadruples[i]._result=quadruples[gotoindex]._result;
        }
        if(quadruples[i]._operator=="ctn")
        {
            quadruples[i]._result=to_string(gotoindex-1);
        }
        if((quadruples[i]._operator=="ifz"))
        {
            i=stoi(quadruples[i]._result);
        }
        }
        quadruple temp;
        temp._operator = "ljmp";
        temp._arg1 = "";
        temp._arg2 = "";
        temp._result = to_string(gotoindex-1);
        quadruples.push_back(temp);

        insideLoop --;
    }
#line 2278 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 891 "c_lang.y" /* yacc.c:1646  */
    {
        delete_var_list(active_func_name, level);
        level --;

        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);

        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val;
        int gotoindex = (yyvsp[-2].type_id).index;
        //  cout<<"$1.index :"<<$1.index<<" $2.val= "<<$3.val<<endl;
        quadruples[gotoindex]._result = to_string(gotoindex + (yyvsp[0].type_id).val + 2);

        for(int i =gotoindex+1;i<gotoindex + (yyvsp[0].type_id).val + 2 && i< quadruples.size();i++ )
        {
            //string s=jmp;
            if(quadruples[i]._operator=="jmp")
            {
            quadruples[i]._result=quadruples[gotoindex]._result;
            }
            if(quadruples[i]._operator=="ctn")
            {
            quadruples[i]._result=to_string(gotoindex-1);
            }
            if((quadruples[i]._operator=="ifz"))
            {
            i=stoi(quadruples[i]._result);
            }
        }
        quadruple temp;
        temp._operator = "ljmp";
        temp._arg1 = "";
        temp._arg2 = "";
        temp._result = to_string(gotoindex-1);
        quadruples.push_back(temp);

        insideLoop --;
    }
#line 2319 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 928 "c_lang.y" /* yacc.c:1646  */
    {
        delete_var_list(active_func_name, level);
        level --;

        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);

        (yyval.type_id).val = (yyvsp[-3].type_id).val + (yyvsp[-2].type_id).val+(yyvsp[0].type_id).val;
        int gotoindex = (yyvsp[-3].type_id).index;
        cout<<"$1.index :"<<(yyvsp[-3].type_id).index<<" $2.val= "<<(yyvsp[-2].type_id).val<<endl;
        quadruples[gotoindex]._result = to_string(gotoindex + (yyvsp[-2].type_id).val+ (yyvsp[0].type_id).val + 2);


        for(int i =gotoindex+1;i<gotoindex + (yyvsp[-2].type_id).val+ (yyvsp[0].type_id).val + 2 && i< quadruples.size();i++ )
        {
            //string s=jmp;
            if(quadruples[i]._operator=="jmp")
            {
                quadruples[i]._result=quadruples[gotoindex]._result;
            }
            if(quadruples[i]._operator=="ctn")
            {
                quadruples[i]._result=to_string(gotoindex-1);
            }
            if((quadruples[i]._operator=="ifz"))
            {
                i=stoi(quadruples[i]._result);
            }
        }
        quadruple temp;
        temp._operator = "ljmp";
        temp._arg1 = "";
        temp._arg2 = "";
        temp._result = to_string(gotoindex-1);
        quadruples.push_back(temp);

        insideLoop --;
    }
#line 2361 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 970 "c_lang.y" /* yacc.c:1646  */
    {
        insideLoop ++;

        (yyval.type_id).index = quadruples.size();
        (yyval.type_id).val = (yyvsp[-1].type_id).val+ (yyvsp[0].type_id).val+1;
        quadruple temp;
        temp._operator = "ifF";
        temp._arg1 = string((yyvsp[0].type_id).sval);
        temp._arg2 = "";
        temp._result = "";
        quadruples.push_back(temp);
    }
#line 2378 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 985 "c_lang.y" /* yacc.c:1646  */
    {

        insideLoop ++;

        (yyval.type_id).index = quadruples.size();
        (yyval.type_id).val = (yyvsp[-1].type_id).val+1;
        quadruple temp;
        temp._operator = "ifF";
        temp._arg1 = string((yyvsp[-1].type_id).sval);
        temp._arg2 = "";
        temp._result = "";
        quadruples.push_back(temp);
        level ++;
    }
#line 2397 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 1002 "c_lang.y" /* yacc.c:1646  */
    { level ++; }
#line 2403 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 1003 "c_lang.y" /* yacc.c:1646  */
    {
        delete_var_list(active_func_name, level);
        level --;

        if (!isMatch((yyvsp[-3].type_id).type, "int")) {
            errorLine("int expected in switch case");
        }

        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2418 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1014 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2426 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1021 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 0;
        (yyval.type_id).type = setVoidType();
    }
#line 2435 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1025 "c_lang.y" /* yacc.c:1646  */
    { level ++; }
#line 2441 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1026 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val;
        delete_var_list(active_func_name, level);
        level --;
        (yyval.type_id).type = strdup((yyvsp[-1].type_id).type);
    }
#line 2452 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1036 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2461 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1041 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val;
        if (!isVoidType((yyvsp[-1].type_id).type))
            (yyval.type_id).type = strdup((yyvsp[-1].type_id).type);
        else
            (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2473 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1052 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 0;
        (yyval.type_id).type = setVoidType();
    }
#line 2482 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1057 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val;
        (yyval.type_id).type = strdup((yyvsp[-1].type_id).type);
    }
#line 2491 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1068 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).type = (yyvsp[0].type_id).type;
    }
#line 2501 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1074 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val;
        (yyval.type_id).sval = (yyvsp[-1].type_id).sval;
        (yyval.type_id).type = (yyvsp[-1].type_id).type;
    }
#line 2511 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1082 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2521 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1088 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).type = setIntType();
    }
#line 2531 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1094 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).type = setIntType();
    }
#line 2541 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1100 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).type = (yyvsp[0].type_id).type;
    }
#line 2551 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1109 "c_lang.y" /* yacc.c:1646  */
    {
        string datatype;
        bool isExists = checkForVariable((yyvsp[-2].type_id).sval, datatype, active_func_name, level, true);

        if (!isExists) {
            errorLine("Variable '" + Variable(string((yyvsp[-2].type_id).sval)) + "' is not declared");
            (yyval.type_id).type = setErrorType();
        }
        else {
            if (!isErrorType((yyvsp[0].type_id).type)) {

                if (isVoidType((yyvsp[0].type_id).type)) {
                    errorLine("void value not ignored as it ought to be");
                }
                else if (!isMatch(datatype, string((yyvsp[0].type_id).type))) {
                    warning("Implicit type conversion from " + string((yyvsp[0].type_id).type) + " to " + datatype);
                }
                (yyval.type_id).val = (yyvsp[0].type_id).val + 2;
                (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
                string temp = get_next_temp();
                (yyval.type_id).sval = strdup(temp.c_str());
                quadruples.push_back(quadruple("=", string((yyvsp[0].type_id).sval), "", string((yyvsp[-2].type_id).sval)));
                quadruples.push_back(quadruple("=", string((yyvsp[0].type_id).sval), "", temp));

            }
        }
    }
#line 2583 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1140 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val + 1;
        string temp = get_next_temp();
        (yyval.type_id).sval = strdup(temp.c_str());
        quadruples.push_back(quadruple(string((yyvsp[-1].type_id).sval), string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), temp));
        quadruples[(yyvsp[-1].type_id).index]._result = to_string((yyvsp[-1].type_id).index + (yyvsp[0].type_id).val + 1);
        quadruples[(yyvsp[-1].type_id).index]._arg1 = (yyvsp[-2].type_id).sval;
    }
#line 2596 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1152 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        (yyval.type_id).index = quadruples.size();
        quadruples.push_back(quadruple("ifT", "", "", ""));
        (yyval.type_id).sval = strdup((yyvsp[0].type_id).sval);
    }
#line 2607 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1159 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        (yyval.type_id).index = quadruples.size();
        quadruples.push_back(quadruple("ifF", "", "", ""));
        (yyval.type_id).sval = strdup((yyvsp[0].type_id).sval);
    }
#line 2618 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1169 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = setIntType();
        string temp = get_next_temp();
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val + 1;
        quadruples.push_back(quadruple(string((yyvsp[-1].type_id).sval), string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), temp));
    }
#line 2630 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1180 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = (yyvsp[-2].type_id).type;
        string temp = get_next_temp();
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val + 1;
        quadruples.push_back(quadruple("+", string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), temp));
    }
#line 2642 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1188 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = (yyvsp[-2].type_id).type;
        string temp = get_next_temp();
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val + 1;
        quadruples.push_back(quadruple("-", string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), temp));
    }
#line 2654 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1196 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = (yyvsp[0].type_id).type;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).val = (yyvsp[0].type_id).val;
    }
#line 2664 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1205 "c_lang.y" /* yacc.c:1646  */
    {
        string temp = get_next_temp();
        (yyval.type_id).type = (yyvsp[-2].type_id).type;
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val + 1;
        quadruples.push_back(quadruple("*", string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), temp));
	}
#line 2676 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1213 "c_lang.y" /* yacc.c:1646  */
    {
        string temp = get_next_temp();
        (yyval.type_id).type = (yyvsp[-2].type_id).type;
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val + 1;
        quadruples.push_back(quadruple("/", string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), temp));
    }
#line 2688 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1221 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = (yyvsp[0].type_id).type;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).val = (yyvsp[0].type_id).val;
    }
#line 2698 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1230 "c_lang.y" /* yacc.c:1646  */
    {
        string temp = get_next_temp();
        (yyval.type_id).type = (yyvsp[-1].type_id).type;
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[-1].type_id).val + 1;
        quadruples.push_back(quadruple("=", (yyvsp[-1].type_id).sval, "",  temp));
	}
#line 2710 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1238 "c_lang.y" /* yacc.c:1646  */
    {
        string datatype;
        bool isExists = checkForVariable((yyvsp[0].type_id).sval, datatype, active_func_name, level, true);
        if (!isExists) {
            errorLine("Variable '" + Variable(string((yyvsp[0].type_id).sval)) + "' is not declared");
            (yyval.type_id).type = setErrorType();
        }
        else {
            (yyval.type_id).type = strdup(datatype.c_str());
        }

        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
    }
#line 2728 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1252 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = (yyvsp[0].type_id).type;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
    }
#line 2737 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1257 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = (yyvsp[0].type_id).type;
        string temp = get_next_temp(string((yyvsp[0].type_id).sval));
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[0].type_id).val + 2;

        // cout << $$.val << "\n";
        quadruples.push_back(quadruple("assign", (yyval.type_id).type, "1",  temp));
        quadruples.push_back(quadruple("=", "t" + string((yyvsp[0].type_id).sval), "",  temp));
    }
#line 2752 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1272 "c_lang.y" /* yacc.c:1646  */
    {
		(yyval.type_id) = (yyvsp[-2].type_id);
        ab_symtab.patch((yyvsp[-2].type_id).sval, (yyvsp[-1].type_id).sval);
        vector<string> dim = makedimlist((yyvsp[-1].type_id).sval);

        (yyval.type_id).val = (yyvsp[-1].type_id).val;
        // cout << $$.val << " quads handled by declaration. \n";
	}
#line 2765 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1284 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
    }
#line 2774 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1289 "c_lang.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-2].type_id).val;
        (yyval.type_id).sval=(yyvsp[-2].type_id).sval;
        strcat((yyval.type_id).sval,",");
        strcat((yyval.type_id).sval, (yyvsp[0].type_id).sval);
	}
#line 2785 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1299 "c_lang.y" /* yacc.c:1646  */
    {
        string datatype;
        bool isExists = checkForVariable((yyvsp[0].type_id).sval, datatype, active_func_name, level, false);
        if (!isExists) {
            variable newVar((yyvsp[0].type_id).sval, datatype, "0", false, dummy, active_func_name, level);
            (yyval.type_id).index = quadruples.size();
            (yyval.type_id).val = 1;
            (yyval.type_id).sval = (yyvsp[0].type_id).sval;
            quadruples.push_back(quadruple("assign", "(type)", "1", (yyvsp[0].type_id).sval));
            ab_symtab.insertintosymtab(newVar, (yyval.type_id).index);
            // cout << "Inserted into symtab : " << string($1.sval) << " ";
        }

	}
#line 2804 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1314 "c_lang.y" /* yacc.c:1646  */
    {
        string datatype;
        bool isExists = checkForVariable((yyvsp[-2].type_id).sval, datatype, active_func_name, level, false);
        if (!isExists) {
            variable newVar((yyvsp[-2].type_id).sval, datatype, "0", false, dummy, active_func_name, level);
            (yyval.type_id).index = quadruples.size();
            (yyval.type_id).val = 1 + (yyvsp[0].type_id).val;
            (yyval.type_id).sval = (yyvsp[-2].type_id).sval;
            quadruples.push_back(quadruple("assign", "(type)", (yyvsp[0].type_id).sval, (yyvsp[-2].type_id).sval));
            ab_symtab.insertintosymtab(newVar, (yyval.type_id).index);
            // cout << "Inserted into symtab : " << string($1.sval) << " ";
        }
	}
#line 2822 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1328 "c_lang.y" /* yacc.c:1646  */
    {
    	string datatype;
        vector<string> dim = makedimlist((yyvsp[0].type_id).sval);
        bool isExists = checkForVariable((yyvsp[-1].type_id).sval, datatype, active_func_name, level, false);
        if (!isExists) {
            variable newVar((yyvsp[-1].type_id).sval, datatype, "0", true, dim, active_func_name, level);
            (yyval.type_id).index = quadruples.size();
            (yyval.type_id).val = 1 + (yyvsp[0].type_id).val;
            (yyval.type_id).sval = (yyvsp[-1].type_id).sval;
            quadruples.push_back(quadruple("assign", "(type)", "expres", (yyvsp[-1].type_id).sval));
            ab_symtab.insertintosymtab(newVar, (yyval.type_id).index);
            // cout << "Inserted into symtab : " << string($1.sval) << " ";
        }
    }
#line 2841 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1346 "c_lang.y" /* yacc.c:1646  */
    {
        if(string((yyvsp[-1].type_id).type) == "float"){
            errorLine("Float cannot be passed as a dimension to an array.");
            return 1;
        }

        (yyval.type_id)=(yyvsp[-1].type_id);
        (yyval.type_id).val = 1;
        quadruples.push_back(quadruple("=", string((yyvsp[-1].type_id).sval), "",  "expres"));
	}
#line 2856 "c_lang.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1357 "c_lang.y" /* yacc.c:1646  */
    {
        if(string((yyvsp[-2].type_id).type) == "float"){
            errorLine("Float cannot be passed as a dimension to an array.");
            return 1;
        }

        (yyval.type_id)=(yyvsp[-2].type_id);
        (yyval.type_id).val = (yyvsp[0].type_id).val + 1;
        quadruples.push_back(quadruple("*", string((yyvsp[-2].type_id).sval), "expres",  "expres"));

		strcat((yyval.type_id).sval,",");
		strcat((yyval.type_id).sval,(yyvsp[0].type_id).sval);
	}
#line 2874 "c_lang.tab.c" /* yacc.c:1646  */
    break;


#line 2878 "c_lang.tab.c" /* yacc.c:1646  */
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
#line 1371 "c_lang.y" /* yacc.c:1906  */


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

    if(!errorFound){
        cout << "Intermediate Code in Quadruple Format:" << "\n";
        cout << setw(3) << "" << "      " << setw(6) << "OPER" << " | " << setw(7) << "ARG1" << " | " << setw(7) << "ARG2" << " | " << setw(7) << "RESULT" << "\n";
        for(int i = 0; i < quadruples.size(); ++i){
            quadruple quad = quadruples[i];
            cout << setw(3) << i << "      " << setw(6) << quad._operator << " | " << setw(7) << quad._arg1 << " | " << setw(7) << quad._arg2 << " | " << setw(7) << quad._result << "\n";
        }
    }

}

void yyerror(const char *s) {
    errorLine(string(s));
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
bool isVoidType(const char *type) {
    if (isMatch(type, "void"))    return true;
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
bool isVoidType(string type) {
    if (isMatch(type, "void"))    return true;
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
char* setVoidType() {
    return strdup("void");
}
char* setIntType() {
    return strdup("int");
}
bool isInsideFunc() {
    return !(active_func_name == "");
}
void reset_active_function() {
    active_func_name = "";
}
void errorLine(string errorMsg) {
    errorFound = true;
    cout << "Error at line " << lineNo << " : " << errorMsg << endl;
}
void warning(string warningMsg) {
    cout << "Warning at line " << lineNo << " : " << warningMsg << endl;
}
bool isVariableInSymtab(string varname) {
    if(ab_symtab.search(varname) == -1)
        return false;
    else
        return true;
}
// If flag = false : check for case like ----- int a = 3;
// If flag = true : check for case like  ----- a = 3;
// Return false if error
// else return true
bool checkForVariable(string var_name, string &datatype, string active_func, int cur_level, bool flag) {

    if (!flag) {
        function_record *r;
        bool varExists = false;

        // Check if variable is already declared
        int cur_level_of_var;
        if (ab_symtab.search_var(var_name, cur_level_of_var, active_func, datatype)) {
            if (cur_level_of_var == cur_level) {
                varExists = true;
                errorLine("Variable already declared in same scope : " + Variable(string(var_name)));
                return varExists;
            }
        }
        if (cur_level == 2) {
            function_record *func;
            var_record *r;
            if ( symtab.search_function(active_func, func) ) {
                if(func->search_param(var_name, r)) {
                    varExists = true;
                    errorLine("Redeclaration of parameter '" + Variable(string(var_name)) + "' as variable" );
                    return varExists;
                }
            }
        }

        return varExists;
    }
    else {
    // If flag = true : check for case like  ----- a = 3;
    // Variable should be declared somewhere

        function_record *r;
        bool varExists = false;
        bool found = false;

        // Check if variable is already declared as a variable (either global or local within a function)
        int cur_level_of_var;
        if (ab_symtab.search_var(var_name, cur_level_of_var, active_func, datatype)) {
            found = true;
            if (cur_level_of_var == cur_level) {
                varExists = true;
                // Variable already declared in same scope
                return varExists;
            }
        }
        if (found) {
            // If the variable is not global
            if (cur_level_of_var > 0)
                return true;
        }

        // Now, either variable is not declared, or declared in parameters or declared in global scope
        {
            function_record *func;
            var_record *r;
            if ( symtab.search_function(active_func, func) ) {
                if(func->search_param(var_name, r)) {
                    varExists = true;
                    // "Declared as parameter"
                    datatype = r->type;
                    return varExists;
                }
            }
            else if (found) {
                return true;
            }
        }

        if (!varExists) {
            // errorLine("Variable : " + var_name + " is not declared");
            return false;
        }
    }
}
void delete_var_list(string function_name, int level) {
    ab_symtab.delete_var_from_level(function_name, level);
}
bool isCompatible(string type1, string type2) {
    return true;
    cout << type1 << " " << type2 << endl;
    if (type1 == type2)
        return true;
    if ( type1 == "float" && type2 == "int" )
        return true;
    if ( type2 == "float" && type1 == "int" )
        return true;
    return false;
}
string Variable(string str) {
    if (str == "")
        return "";
    return str.substr(1);
}
