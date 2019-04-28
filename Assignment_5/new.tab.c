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
#line 1 "new.y" /* yacc.c:339  */

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

#line 446 "new.tab.c" /* yacc.c:339  */

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
   by #include "new.tab.h".  */
#ifndef YY_YY_NEW_TAB_H_INCLUDED
# define YY_YY_NEW_TAB_H_INCLUDED
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
    REL_OP = 273,
    RETURN = 274,
    TYPE = 275,
    VOID = 276
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 381 "new.y" /* yacc.c:355  */

    struct {
        struct indexlist * indexlist;
        char* type;
        int val;
        int index;
        int len;
        char* sval;
    } type_id;

#line 519 "new.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_NEW_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 536 "new.tab.c" /* yacc.c:358  */

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
#define YYLAST   270

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  188

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

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
      24,    25,    32,    30,    26,    31,     2,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    28,    27,
       2,    29,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    22,     2,    23,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   426,   426,   427,   428,   429,   433,   455,   464,   471,
     471,   492,   492,   513,   535,   561,   583,   594,   598,   602,
     606,   607,   611,   645,   705,   715,   739,   743,   747,   752,
     757,   761,   780,   790,   794,   798,   803,   808,   812,   819,
     830,   843,   850,   862,   862,   876,   884,   897,   897,   934,
     945,   945,   984,  1014,  1049,  1067,  1086,  1119,  1119,  1130,
    1139,  1161,  1161,  1172,  1179,  1184,  1184,  1194,  1199,  1211,
    1216,  1216,  1226,  1231,  1244,  1249,  1260,  1266,  1274,  1280,
    1286,  1292,  1301,  1332,  1344,  1351,  1361,  1372,  1380,  1388,
    1397,  1405,  1413,  1422,  1430,  1444,  1449,  1464,  1476,  1481,
    1491,  1506,  1520,  1538,  1549
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "IDENTIFIER", "INT", "FLOAT",
  "OR", "IF", "ELSE", "FOR", "WHILE", "SWITCH", "CASE", "DEFAULT", "BREAK",
  "CONTINUE", "AND", "REL_OP", "RETURN", "TYPE", "VOID", "'{'", "'}'",
  "'('", "')'", "','", "';'", "':'", "'='", "'+'", "'-'", "'*'", "'/'",
  "'['", "']'", "$accept", "START", "function_declaration",
  "function_result_assignment", "function_head", "$@1", "$@2",
  "param_list_declaration", "param_declaration",
  "variable_declaration_list", "variable_declaration", "datatype",
  "function_call", "arg_list", "statement", "loopstatement",
  "conditional_statement", "$@3", "loopconditional_statement", "$@4",
  "else_mark", "loop_statement", "$@5", "FOREXP", "WHILEEXP",
  "looplabeled_statement", "$@6", "if_exp", "labeled_statement", "$@7",
  "compound_statement", "$@8", "statement_list", "loopcompound_statement",
  "$@9", "loopstatement_list", "expression_statement", "expression_cover",
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
     275,   276,   123,   125,    40,    41,    44,    59,    58,    61,
      43,    45,    42,    47,    91,    93
};
# endif

#define YYPACT_NINF -87

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-87)))

#define YYTABLE_NINF -77

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      56,    -1,     6,     8,   -87,    -6,   -87,   106,    -9,    -4,
       2,   -87,   -87,   -87,    -3,    13,    39,    42,   -87,   -87,
      45,    34,   -87,   237,   -87,    59,   -87,    57,    39,   -87,
     -87,   116,   131,    50,   -15,   -87,   -87,    59,    27,    66,
      68,    77,    79,   108,    81,    20,    45,    96,    58,   -87,
     -87,   -87,   -87,     9,   -87,   237,   -87,   -87,   193,   -87,
     126,    95,   -87,   -87,   -87,   -87,   -87,   120,   163,   -87,
      28,   101,    39,    39,    39,    39,    97,   165,    39,    58,
      20,    58,    58,   109,   237,   -87,   -87,   237,    98,   -87,
     101,   171,   114,   171,   133,   -87,   -87,   -87,   -87,    58,
      58,   -87,   -87,   -87,    59,   -87,   174,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   111,    20,   245,   128,
     -87,   -87,   215,   -87,   -87,   -87,   143,   151,   153,   169,
     -87,   -87,   190,   -87,   -87,   -87,   171,   -87,   -87,   -87,
     171,   -87,   -87,   237,   126,   126,   -87,   -87,    39,   -87,
      58,   -87,   -87,   237,   -87,    58,   -87,   -87,   -87,   171,
     175,   133,   -87,   -87,   -87,   148,   237,   -87,   185,   -87,
     146,   -87,   171,   -87,   -87,   -87,   -87,   -87,   158,   208,
     186,   -87,   194,   171,   -87,   -87,   171,   -87
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     0,     3,   100,     0,    98,
       0,     1,     4,     5,     8,     9,     0,     0,   102,    97,
       0,    11,     7,     0,    13,     0,    95,    94,     0,    96,
     101,    89,    92,     0,   100,    99,    14,     0,    94,     0,
       0,     0,     0,     0,     0,     0,     0,    65,     0,    74,
      67,    26,    27,     0,    50,     0,    32,    28,     0,    29,
       0,    76,    78,    79,    80,    81,    30,     0,     0,    16,
       0,     0,     0,     0,     0,     0,   103,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    64,     0,     0,    76,
      81,     0,    76,     0,    41,     6,    68,    84,    85,     0,
       0,    75,    17,    10,     0,    22,     0,    24,    93,    87,
      88,    90,    91,   104,    12,    82,     0,     0,     0,    76,
      61,    63,     0,    77,    20,    21,     0,     0,     0,    70,
      37,    18,     0,    52,    33,    34,     0,    38,    35,    36,
       0,    51,    49,     0,    86,    83,    15,    23,     0,    60,
      54,    56,    43,     0,    66,     0,    39,    40,    69,     0,
       0,    45,    53,    42,    25,    55,     0,    62,    76,    72,
       0,    19,     0,    44,    47,    71,    73,    46,     0,     0,
       0,    48,     0,     0,    57,    59,     0,    58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -87,   -87,   218,   -87,   -87,   -87,   -87,   187,   127,   -87,
     -87,   -87,   -87,   -87,   -54,   -38,   -87,   -87,   -87,   -87,
      69,   -86,   -87,   -87,   -87,   -87,   -87,   -76,   -66,   -87,
     -87,   -87,   145,   -87,   -87,   -87,   -45,   -12,   -42,   -87,
     -87,   -87,   -87,    -7,   134,   -68,    75,   213,   -87,   160
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    23,     5,    25,    37,    68,    69,   130,
     131,   132,    29,   106,    50,   133,    51,   166,   134,   178,
     143,    52,    93,    53,    54,   181,   186,    55,    56,   153,
      57,    87,    58,   138,   159,   170,    59,    60,    61,    62,
      63,   100,    64,    65,    31,    32,    66,     8,     9,    18
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      85,    94,   107,     7,    96,   135,    89,   135,    11,    30,
      10,    92,    26,    38,    16,   136,    14,   136,    19,    17,
      22,    71,    20,    26,    38,   137,    21,   137,     1,     2,
     121,    26,    27,    48,    91,   117,    88,    89,    24,    89,
     119,    90,    26,    27,    48,    33,   139,    49,   139,    34,
     135,    70,    28,   105,   135,   141,    78,    89,    89,    36,
     136,    26,    38,    28,   136,   109,   110,   116,    96,   118,
     137,   115,   150,   135,   137,     6,     1,     2,    13,    67,
     164,    70,    48,   136,   135,    76,   135,   144,   145,   163,
      79,   139,    80,   137,   136,   139,   136,   135,   161,   167,
     135,    81,   162,    82,   137,    97,   137,   136,   165,    84,
     136,    83,   173,   168,   139,    98,    99,   137,    97,    86,
     137,   169,   101,   123,   102,   139,   108,   139,    98,    99,
      15,    17,   176,    97,   177,    16,   149,   120,   139,   140,
      17,   139,   142,    98,    99,   185,    72,    73,   187,    26,
      38,   124,   125,   152,    39,   -76,    40,    41,   126,    43,
      44,   127,   128,    74,    75,   -76,   -76,   155,   129,   175,
      48,   179,   180,    49,    26,    38,   124,   125,   156,    39,
     157,    40,    41,   126,    43,    44,   127,   128,   103,   104,
     114,   104,   158,   129,   160,    48,    26,    38,    49,   147,
     148,    39,   171,    40,    41,    42,    43,    44,   111,   112,
     174,   182,    45,    46,   183,    47,    95,    48,    26,    38,
      49,    12,   184,    39,    77,    40,    41,    42,    43,    44,
     172,   146,   122,    35,    45,    46,   113,    47,   154,    48,
      26,    38,    49,     0,     0,    39,     0,    40,    41,    42,
      43,    44,    97,     0,     0,     0,    45,    46,     0,    47,
       0,    48,    98,    99,    49,     0,     0,     0,     0,     0,
     151
};

static const yytype_int16 yycheck[] =
{
      45,    55,    70,     4,    58,    91,    48,    93,     0,    16,
       4,    53,     3,     4,    29,    91,    22,    93,    27,    34,
      23,    28,    26,     3,     4,    91,    24,    93,    20,    21,
      84,     3,     4,    24,    25,    80,    48,    79,    25,    81,
      82,    48,     3,     4,    24,     3,    91,    27,    93,     4,
     136,    24,    24,    25,   140,    93,    29,    99,   100,    25,
     136,     3,     4,    24,   140,    72,    73,    79,   122,    81,
     136,    78,   117,   159,   140,     0,    20,    21,     3,    20,
     148,    24,    24,   159,   170,    35,   172,    99,   100,   143,
      24,   136,    24,   159,   170,   140,   172,   183,   136,   153,
     186,    24,   140,    24,   170,     7,   172,   183,   150,    28,
     186,     3,   166,   155,   159,    17,    18,   183,     7,    23,
     186,   159,    27,    25,     4,   170,    25,   172,    17,    18,
      24,    34,   170,     7,   172,    29,    25,    28,   183,    25,
      34,   186,     9,    17,    18,   183,    30,    31,   186,     3,
       4,     5,     6,    25,     8,     7,    10,    11,    12,    13,
      14,    15,    16,    32,    33,    17,    18,    24,    22,    23,
      24,    13,    14,    27,     3,     4,     5,     6,    27,     8,
      27,    10,    11,    12,    13,    14,    15,    16,    25,    26,
      25,    26,    23,    22,     4,    24,     3,     4,    27,    25,
      26,     8,    27,    10,    11,    12,    13,    14,    74,    75,
      25,     3,    19,    20,    28,    22,    23,    24,     3,     4,
      27,     3,    28,     8,    37,    10,    11,    12,    13,    14,
     161,   104,    87,    20,    19,    20,    76,    22,    23,    24,
       3,     4,    27,    -1,    -1,     8,    -1,    10,    11,    12,
      13,    14,     7,    -1,    -1,    -1,    19,    20,    -1,    22,
      -1,    24,    17,    18,    27,    -1,    -1,    -1,    -1,    -1,
      25
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    20,    21,    37,    38,    40,    82,     4,    83,    84,
       4,     0,    38,    82,    22,    24,    29,    34,    85,    27,
      26,    24,    23,    39,    25,    41,     3,     4,    24,    48,
      79,    80,    81,     3,     4,    83,    25,    42,     4,     8,
      10,    11,    12,    13,    14,    19,    20,    22,    24,    27,
      50,    52,    57,    59,    60,    63,    64,    66,    68,    72,
      73,    74,    75,    76,    78,    79,    82,    20,    43,    44,
      24,    79,    30,    31,    32,    33,    35,    43,    29,    24,
      24,    24,    24,     3,    28,    72,    23,    67,    73,    74,
      79,    25,    74,    58,    50,    23,    50,     7,    17,    18,
      77,    27,     4,    25,    26,    25,    49,    81,    25,    79,
      79,    80,    80,    85,    25,    79,    73,    72,    73,    74,
      28,    50,    68,    25,     5,     6,    12,    15,    16,    22,
      45,    46,    47,    51,    54,    57,    63,    64,    69,    72,
      25,    51,     9,    56,    73,    73,    44,    25,    26,    25,
      72,    25,    25,    65,    23,    24,    27,    27,    23,    70,
       4,    51,    51,    50,    81,    74,    53,    50,    74,    51,
      71,    27,    56,    50,    25,    23,    51,    51,    55,    13,
      14,    61,     3,    28,    28,    51,    62,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    37,    37,    37,    38,    38,    39,    41,
      40,    42,    40,    40,    40,    43,    43,    44,    45,    46,
      47,    47,    48,    48,    49,    49,    50,    50,    50,    50,
      50,    50,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    52,    52,    53,    52,    54,    54,    55,    54,    56,
      58,    57,    57,    57,    59,    59,    60,    62,    61,    61,
      63,    65,    64,    64,    66,    67,    66,    68,    68,    69,
      70,    69,    71,    71,    72,    72,    73,    73,    74,    74,
      74,    74,    75,    76,    77,    77,    78,    79,    79,    79,
      80,    80,    80,    81,    81,    81,    81,    82,    83,    83,
      84,    84,    84,    85,    85
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     5,     3,     0,     0,
       6,     0,     6,     4,     4,     3,     1,     2,     1,     3,
       1,     1,     3,     4,     1,     3,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     4,     0,     6,     2,     4,     0,     6,     1,
       0,     3,     3,     4,     4,     5,     4,     0,     5,     3,
       4,     0,     5,     3,     2,     0,     4,     1,     2,     2,
       0,     4,     1,     2,     1,     2,     1,     3,     1,     1,
       1,     1,     3,     3,     1,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     1,     1,     3,     1,     3,
       1,     3,     2,     3,     4
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
#line 434 "new.y" /* yacc.c:1646  */
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
#line 1788 "new.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 456 "new.y" /* yacc.c:1646  */
    {
        delete_var_list(active_func_name, level);
        level--;
        reset_active_function();
    }
#line 1798 "new.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 465 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).index = quadruples.size();
        quadruples.push_back(quadruple("assign", "(type)", "1", "(funcvar)"));
    }
#line 1807 "new.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 471 "new.y" /* yacc.c:1646  */
    { level ++; }
#line 1813 "new.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 472 "new.y" /* yacc.c:1646  */
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
#line 1838 "new.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 492 "new.y" /* yacc.c:1646  */
    { level ++; }
#line 1844 "new.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 493 "new.y" /* yacc.c:1646  */
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
#line 1869 "new.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 514 "new.y" /* yacc.c:1646  */
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
#line 1895 "new.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 536 "new.y" /* yacc.c:1646  */
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
#line 1922 "new.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 562 "new.y" /* yacc.c:1646  */
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
#line 1948 "new.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 584 "new.y" /* yacc.c:1646  */
    {
    active_func_param_list.clear();
    (yyval.type_id).len = 1;
    var_record param((yyvsp[0].type_id).sval, (yyvsp[0].type_id).type, /* is_parameter = */ true, level) ;
    active_func_param_list.push_back(param);
    (yyval.type_id).type = setNoErrorType();
}
#line 1960 "new.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 594 "new.y" /* yacc.c:1646  */
    { (yyval.type_id).type = (yyvsp[-1].type_id).sval; (yyval.type_id).sval = (yyvsp[0].type_id).sval; }
#line 1966 "new.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 602 "new.y" /* yacc.c:1646  */
    {}
#line 1972 "new.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 606 "new.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup("int"); }
#line 1978 "new.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 607 "new.y" /* yacc.c:1646  */
    { (yyval.type_id).type = strdup("float"); }
#line 1984 "new.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 612 "new.y" /* yacc.c:1646  */
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
#line 2022 "new.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 646 "new.y" /* yacc.c:1646  */
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
#line 2082 "new.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 706 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).len = 1;
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).type = setNoErrorType();
        string datatype = (yyvsp[0].type_id).type;

        var_record arg((yyvsp[0].type_id).sval, datatype, false, level) ;
        called_arg_list.push_back(arg);
    }
#line 2096 "new.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 716 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val;
        string datatype = (yyvsp[-2].type_id).type;
        (yyval.type_id).type = setNoErrorType();

        var_record arg((yyvsp[0].type_id).sval, datatype, /* is_parameter = */ false, level) ;

        called_arg_list.push_back(arg);
        (yyval.type_id).len = (yyvsp[0].type_id).len + 1;

        // cout << "Called args are: ";
        // for(auto it = called_arg_list.begin(); it != called_arg_list.end(); ++it){
        //     cout << it -> name << " ";
        // }
        // cout << "\n";

        if (isErrorType((yyvsp[-2].type_id).type)) {
            (yyval.type_id).type = setErrorType();
        }
    }
#line 2121 "new.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 740 "new.y" /* yacc.c:1646  */
    {
          (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
      }
#line 2129 "new.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 744 "new.y" /* yacc.c:1646  */
    {
          (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
      }
#line 2137 "new.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 748 "new.y" /* yacc.c:1646  */
    {
          (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
          (yyval.type_id).val = (yyvsp[0].type_id).val;
      }
#line 2146 "new.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 753 "new.y" /* yacc.c:1646  */
    {
          (yyval.type_id).type = setVoidType();
          (yyval.type_id).val = (yyvsp[0].type_id).val;
      }
#line 2155 "new.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 758 "new.y" /* yacc.c:1646  */
    {
          (yyval.type_id).type = setVoidType();
      }
#line 2163 "new.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 762 "new.y" /* yacc.c:1646  */
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
#line 2186 "new.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 781 "new.y" /* yacc.c:1646  */
    {
          if (!insideSwitchCase)
              errorLine("Label conditions not inside switch statement");

          (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
      }
#line 2197 "new.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 791 "new.y" /* yacc.c:1646  */
    {
            (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
        }
#line 2205 "new.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 795 "new.y" /* yacc.c:1646  */
    {
            (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
        }
#line 2213 "new.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 799 "new.y" /* yacc.c:1646  */
    {
            (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
            (yyval.type_id).val = (yyvsp[0].type_id).val;
        }
#line 2222 "new.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 804 "new.y" /* yacc.c:1646  */
    {
            (yyval.type_id).type = setVoidType();
            (yyval.type_id).val = (yyvsp[0].type_id).val;
        }
#line 2231 "new.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 809 "new.y" /* yacc.c:1646  */
    {
            (yyval.type_id).type = setVoidType();
        }
#line 2239 "new.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 813 "new.y" /* yacc.c:1646  */
    {
            if (!insideSwitchCase)
                errorLine("Label conditions not inside switch statement");

            (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
        }
#line 2250 "new.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 819 "new.y" /* yacc.c:1646  */
    {
            (yyval.type_id).index= quadruples.size();
            (yyval.type_id).val=1;

            quadruple temp;
            temp._operator = "jmp";
            temp._arg1 = "";
            temp._arg2 = "";
            temp._result = "";
            quadruples.push_back(temp);
        }
#line 2266 "new.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 830 "new.y" /* yacc.c:1646  */
    {
            (yyval.type_id).val=1;
            quadruple temp;
            temp._operator = "ctn";
            temp._arg1 = "";
            temp._arg2 = "";
            temp._result = "";
            quadruples.push_back(temp);
        }
#line 2280 "new.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 844 "new.y" /* yacc.c:1646  */
    {
          (yyval.type_id).val = (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val;
          int gotoindex = (yyvsp[-1].type_id).index;
          quadruples[gotoindex]._result = to_string(gotoindex + (yyvsp[0].type_id).val + 1);
          (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
      }
#line 2291 "new.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 851 "new.y" /* yacc.c:1646  */
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
#line 2307 "new.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 862 "new.y" /* yacc.c:1646  */
    { level ++; insideSwitchCase ++; }
#line 2313 "new.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 863 "new.y" /* yacc.c:1646  */
    {
            delete_var_list(active_func_name, level);
            level --;

            if ( !isInt((yyvsp[-3].type_id).type) && !isFloat((yyvsp[-3].type_id).type) )
                errorLine("int expected in expression of if-else");

            (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
            insideSwitchCase --;
        }
#line 2328 "new.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 877 "new.y" /* yacc.c:1646  */
    {
            (yyval.type_id).val = (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val;
            int gotoindex = (yyvsp[-1].type_id).index;
            quadruples[gotoindex]._result = to_string(gotoindex + (yyvsp[0].type_id).val + 1);
            (yyval.type_id).type = strdup((yyvsp[0].type_id).type);

        }
#line 2340 "new.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 885 "new.y" /* yacc.c:1646  */
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
#line 2357 "new.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 897 "new.y" /* yacc.c:1646  */
    { level ++; insideSwitchCase ++; }
#line 2363 "new.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 898 "new.y" /* yacc.c:1646  */
    {
        delete_var_list(active_func_name, level);
        level --;

        if ( !isInt((yyvsp[-3].type_id).type) && !isFloat((yyvsp[-3].type_id).type) )
            errorLine("int expected in expression of if-else");

        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
        insideSwitchCase --;
        }
#line 2378 "new.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 935 "new.y" /* yacc.c:1646  */
    {
          (yyval.type_id).val = 1;
          (yyval.type_id).index = quadruples.size();
          quadruples.push_back(quadruple("go", "", "", ""));
      }
#line 2388 "new.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 945 "new.y" /* yacc.c:1646  */
    {level++}
#line 2394 "new.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 946 "new.y" /* yacc.c:1646  */
    {
          delete_var_list(active_func_name, level);
          level --;

          if (!isInt((yyvsp[0].type_id).type) && !isFloat((yyvsp[0].type_id).type))
              errorLine("int expected in expression of while statement");

          (yyval.type_id).type = strdup((yyvsp[0].type_id).type);

        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val;
          int gotoindex = (yyvsp[-2].type_id).index;
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

        }
#line 2437 "new.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 985 "new.y" /* yacc.c:1646  */
    {
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
        }
#line 2471 "new.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1015 "new.y" /* yacc.c:1646  */
    {
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
          }
#line 2506 "new.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1049 "new.y" /* yacc.c:1646  */
    {
            delete_var_list(active_func_name, level);
          //  level --;


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
#line 2528 "new.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1067 "new.y" /* yacc.c:1646  */
    {
           delete_var_list(active_func_name, level);
          // level --;

             if (strcmp((yyvsp[-1].type_id).type, "num") && strcmp((yyvsp[-1].type_id).type, "None")) {
                 yyerror("Type error in condition of for loop");
             }
             (yyval.type_id).index = quadruples.size();
             (yyval.type_id).val = (yyvsp[-2].type_id).val+ (yyvsp[-1].type_id).val+1+ (yyvsp[0].type_id).val ;
             quadruple temp;
             temp._operator = "ifz";
             temp._arg1 = "expres";
             temp._arg2 = "";
             temp._result = "";
             quadruples.push_back(temp);
         }
#line 2549 "new.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1086 "new.y" /* yacc.c:1646  */
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
#line 2567 "new.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1119 "new.y" /* yacc.c:1646  */
    { level ++; }
#line 2573 "new.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1120 "new.y" /* yacc.c:1646  */
    {
          delete_var_list(active_func_name, level);
          level --;

          if (!isMatch((yyvsp[-3].type_id).type, "int")) {
              errorLine("int expected in switch case");
          }

          (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
      }
#line 2588 "new.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1131 "new.y" /* yacc.c:1646  */
    {
          (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
      }
#line 2596 "new.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1140 "new.y" /* yacc.c:1646  */
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
#line 2620 "new.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1161 "new.y" /* yacc.c:1646  */
    { level ++; }
#line 2626 "new.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1162 "new.y" /* yacc.c:1646  */
    {
        delete_var_list(active_func_name, level);
        level --;

        if (!isMatch((yyvsp[-3].type_id).type, "int")) {
            errorLine("int expected in switch case");
        }

        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2641 "new.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1173 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2649 "new.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1180 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 0;
        (yyval.type_id).type = setVoidType();
    }
#line 2658 "new.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1184 "new.y" /* yacc.c:1646  */
    { level ++; }
#line 2664 "new.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1185 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val;
        delete_var_list(active_func_name, level);
        level --;
        (yyval.type_id).type = strdup((yyvsp[-1].type_id).type);
    }
#line 2675 "new.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1195 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2684 "new.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1200 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val;
        if (!isVoidType((yyvsp[-1].type_id).type))
            (yyval.type_id).type = strdup((yyvsp[-1].type_id).type);
        else
            (yyval.type_id).type = strdup((yyvsp[0].type_id).type);

    }
#line 2697 "new.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1212 "new.y" /* yacc.c:1646  */
    {
          (yyval.type_id).val = 0;
          (yyval.type_id).type = setVoidType();
      }
#line 2706 "new.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1216 "new.y" /* yacc.c:1646  */
    { level ++; }
#line 2712 "new.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1217 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val;
        delete_var_list(active_func_name, level);
        level --;
        (yyval.type_id).type = strdup((yyvsp[-1].type_id).type);
      }
#line 2723 "new.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1227 "new.y" /* yacc.c:1646  */
    {
          (yyval.type_id).val = (yyvsp[0].type_id).val;
            (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
      }
#line 2732 "new.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1232 "new.y" /* yacc.c:1646  */
    {
          (yyval.type_id).val = (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val;
          if (!isVoidType((yyvsp[-1].type_id).type))
              (yyval.type_id).type = strdup((yyvsp[-1].type_id).type);
          else
              (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
      }
#line 2744 "new.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1245 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 0;
        (yyval.type_id).type = setVoidType();
    }
#line 2753 "new.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1250 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val;
        (yyval.type_id).type = strdup((yyvsp[-1].type_id).type);
    }
#line 2762 "new.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1261 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).type = (yyvsp[0].type_id).type;
    }
#line 2772 "new.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1267 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-1].type_id).val;
        (yyval.type_id).sval = (yyvsp[-1].type_id).sval;
        (yyval.type_id).type = (yyvsp[-1].type_id).type;
    }
#line 2782 "new.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1275 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).type = strdup((yyvsp[0].type_id).type);
    }
#line 2792 "new.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1281 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).type = setIntType();
    }
#line 2802 "new.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1287 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).type = setIntType();
    }
#line 2812 "new.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1293 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).type = (yyvsp[0].type_id).type;
    }
#line 2822 "new.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1302 "new.y" /* yacc.c:1646  */
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
#line 2854 "new.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1333 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[-1].type_id).val + (yyvsp[0].type_id).val + 1;
        string temp = get_next_temp();
        (yyval.type_id).sval = strdup(temp.c_str());
        quadruples.push_back(quadruple(string((yyvsp[-1].type_id).sval), string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), temp));
        quadruples[(yyvsp[-1].type_id).index]._result = to_string((yyvsp[-1].type_id).index + (yyvsp[0].type_id).val + 1);
        quadruples[(yyvsp[-1].type_id).index]._arg1 = (yyvsp[-2].type_id).sval;
    }
#line 2867 "new.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1345 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        (yyval.type_id).index = quadruples.size();
        quadruples.push_back(quadruple("ifT", "", "", ""));
        (yyval.type_id).sval = strdup((yyvsp[0].type_id).sval);
    }
#line 2878 "new.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1352 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = 1;
        (yyval.type_id).index = quadruples.size();
        quadruples.push_back(quadruple("ifF", "", "", ""));
        (yyval.type_id).sval = strdup((yyvsp[0].type_id).sval);
    }
#line 2889 "new.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1362 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = setIntType();
        string temp = get_next_temp();
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val + 1;
        quadruples.push_back(quadruple(string((yyvsp[-1].type_id).sval), string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), temp));
    }
#line 2901 "new.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1373 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = (yyvsp[-2].type_id).type;
        string temp = get_next_temp();
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val + 1;
        quadruples.push_back(quadruple("+", string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), temp));
    }
#line 2913 "new.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1381 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = (yyvsp[-2].type_id).type;
        string temp = get_next_temp();
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val + 1;
        quadruples.push_back(quadruple("-", string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), temp));
    }
#line 2925 "new.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1389 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = (yyvsp[0].type_id).type;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).val = (yyvsp[0].type_id).val;
    }
#line 2935 "new.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1398 "new.y" /* yacc.c:1646  */
    {
        string temp = get_next_temp();
        (yyval.type_id).type = (yyvsp[-2].type_id).type;
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val + 1;
        quadruples.push_back(quadruple("*", string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), temp));
	}
#line 2947 "new.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1406 "new.y" /* yacc.c:1646  */
    {
        string temp = get_next_temp();
        (yyval.type_id).type = (yyvsp[-2].type_id).type;
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[-2].type_id).val + (yyvsp[0].type_id).val + 1;
        quadruples.push_back(quadruple("/", string((yyvsp[-2].type_id).sval), string((yyvsp[0].type_id).sval), temp));
    }
#line 2959 "new.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1414 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = (yyvsp[0].type_id).type;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
        (yyval.type_id).val = (yyvsp[0].type_id).val;
    }
#line 2969 "new.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1423 "new.y" /* yacc.c:1646  */
    {
        string temp = get_next_temp();
        (yyval.type_id).type = (yyvsp[-1].type_id).type;
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[-1].type_id).val + 1;
        quadruples.push_back(quadruple("=", (yyvsp[-1].type_id).sval, "",  temp));
	}
#line 2981 "new.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1431 "new.y" /* yacc.c:1646  */
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
#line 2999 "new.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1445 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = (yyvsp[0].type_id).type;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
    }
#line 3008 "new.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1450 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).type = (yyvsp[0].type_id).type;
        string temp = get_next_temp(string((yyvsp[0].type_id).sval));
        (yyval.type_id).sval = strdup(temp.c_str());
        (yyval.type_id).val = (yyvsp[0].type_id).val + 2;

        // cout << $$.val << "\n";
        quadruples.push_back(quadruple("assign", (yyval.type_id).type, "1",  temp));
        quadruples.push_back(quadruple("=", "t" + string((yyvsp[0].type_id).val), "",  temp));
    }
#line 3023 "new.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1465 "new.y" /* yacc.c:1646  */
    {
		(yyval.type_id) = (yyvsp[-2].type_id);
        ab_symtab.patch((yyvsp[-2].type_id).sval, (yyvsp[-1].type_id).sval);
        vector<string> dim = makedimlist((yyvsp[-1].type_id).sval);

        (yyval.type_id).val = (yyvsp[-1].type_id).val;
        // cout << $$.val << " quads handled by declaration. \n";
	}
#line 3036 "new.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1477 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[0].type_id).val;
        (yyval.type_id).sval = (yyvsp[0].type_id).sval;
    }
#line 3045 "new.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1482 "new.y" /* yacc.c:1646  */
    {
        (yyval.type_id).val = (yyvsp[-2].type_id).val;
        (yyval.type_id).sval=(yyvsp[-2].type_id).sval;
        strcat((yyval.type_id).sval,",");
        strcat((yyval.type_id).sval, (yyvsp[0].type_id).sval);
	}
#line 3056 "new.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1492 "new.y" /* yacc.c:1646  */
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
#line 3075 "new.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1507 "new.y" /* yacc.c:1646  */
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
#line 3093 "new.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1521 "new.y" /* yacc.c:1646  */
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
#line 3112 "new.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1539 "new.y" /* yacc.c:1646  */
    {
        if(string((yyvsp[-1].type_id).type) == "float"){
            errorLine("Float cannot be passed as a dimension to an array.");
            return 1;
        }

        (yyval.type_id)=(yyvsp[-1].type_id);
        (yyval.type_id).val = 1;
        quadruples.push_back(quadruple("=", string((yyvsp[-1].type_id).sval), "",  "expres"));
	}
#line 3127 "new.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1550 "new.y" /* yacc.c:1646  */
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
#line 3145 "new.tab.c" /* yacc.c:1646  */
    break;


#line 3149 "new.tab.c" /* yacc.c:1646  */
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
#line 1564 "new.y" /* yacc.c:1906  */


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
