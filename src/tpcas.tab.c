/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "src/tpcas.y"

/* Parseur du projet tpc */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "Format.h"
#include "symbole.h"
#include "ParseAsm.h"

int yyerror(char *msg);
int yylex(void);
int yyparse();

extern int lineno;
extern int errorinline;
char name[64];

int help_flag = 0;
int tree_flag = 0;
int varGlob_flag = 0;
int varLoc_flag = 0;
int suiteInstr_flag = 0;


#line 98 "src/tpcas.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "tpcas.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TYPE = 3,                       /* TYPE  */
  YYSYMBOL_VOID = 4,                       /* VOID  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_OR = 9,                         /* OR  */
  YYSYMBOL_AND = 10,                       /* AND  */
  YYSYMBOL_ORDER = 11,                     /* ORDER  */
  YYSYMBOL_EQ = 12,                        /* EQ  */
  YYSYMBOL_IDENT = 13,                     /* IDENT  */
  YYSYMBOL_NUM = 14,                       /* NUM  */
  YYSYMBOL_CHARACTER = 15,                 /* CHARACTER  */
  YYSYMBOL_ADDSUB = 16,                    /* ADDSUB  */
  YYSYMBOL_DIVSTAR = 17,                   /* DIVSTAR  */
  YYSYMBOL_THEN = 18,                      /* THEN  */
  YYSYMBOL_19_ = 19,                       /* ';'  */
  YYSYMBOL_20_ = 20,                       /* ','  */
  YYSYMBOL_21_ = 21,                       /* '('  */
  YYSYMBOL_22_ = 22,                       /* ')'  */
  YYSYMBOL_23_ = 23,                       /* '{'  */
  YYSYMBOL_24_ = 24,                       /* '}'  */
  YYSYMBOL_25_ = 25,                       /* '='  */
  YYSYMBOL_26_ = 26,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 27,                  /* $accept  */
  YYSYMBOL_Prog = 28,                      /* Prog  */
  YYSYMBOL_DeclarVarGlob = 29,             /* DeclarVarGlob  */
  YYSYMBOL_DeclarateursGlob = 30,          /* DeclarateursGlob  */
  YYSYMBOL_DeclFoncts = 31,                /* DeclFoncts  */
  YYSYMBOL_DeclFonct = 32,                 /* DeclFonct  */
  YYSYMBOL_EnTeteFonct = 33,               /* EnTeteFonct  */
  YYSYMBOL_Parametres = 34,                /* Parametres  */
  YYSYMBOL_ListTypVar = 35,                /* ListTypVar  */
  YYSYMBOL_Corps = 36,                     /* Corps  */
  YYSYMBOL_DeclarVarLoc = 37,              /* DeclarVarLoc  */
  YYSYMBOL_DeclarateursLoc = 38,           /* DeclarateursLoc  */
  YYSYMBOL_Affectation = 39,               /* Affectation  */
  YYSYMBOL_SuiteInstr = 40,                /* SuiteInstr  */
  YYSYMBOL_Instr = 41,                     /* Instr  */
  YYSYMBOL_Exp = 42,                       /* Exp  */
  YYSYMBOL_TB = 43,                        /* TB  */
  YYSYMBOL_FB = 44,                        /* FB  */
  YYSYMBOL_M = 45,                         /* M  */
  YYSYMBOL_E = 46,                         /* E  */
  YYSYMBOL_T = 47,                         /* T  */
  YYSYMBOL_F = 48,                         /* F  */
  YYSYMBOL_LValue = 49,                    /* LValue  */
  YYSYMBOL_Arguments = 50,                 /* Arguments  */
  YYSYMBOL_ListExp = 51                    /* ListExp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   115

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  112

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   273


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,     2,     2,     2,     2,     2,
      21,    22,     2,     2,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    19,
       2,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,     2,    24,     2,     2,     2,     2,
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
static const yytype_int16 yyrline[] =
{
       0,    50,    50,    73,    82,    87,    92,    98,   102,   108,
     115,   127,   140,   146,   152,   160,   168,   188,   197,   202,
     219,   235,   240,   246,   252,   257,   263,   268,   276,   281,
     286,   290,   293,   296,   300,   305,   309,   314,   318,   324,
     328,   335,   339,   345,   349,   355,   359,   364,   368,   371,
     376,   380,   383,   390,   396,   400,   406,   409
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TYPE", "VOID", "IF",
  "ELSE", "WHILE", "RETURN", "OR", "AND", "ORDER", "EQ", "IDENT", "NUM",
  "CHARACTER", "ADDSUB", "DIVSTAR", "THEN", "';'", "','", "'('", "')'",
  "'{'", "'}'", "'='", "'!'", "$accept", "Prog", "DeclarVarGlob",
  "DeclarateursGlob", "DeclFoncts", "DeclFonct", "EnTeteFonct",
  "Parametres", "ListTypVar", "Corps", "DeclarVarLoc", "DeclarateursLoc",
  "Affectation", "SuiteInstr", "Instr", "Exp", "TB", "FB", "M", "E", "T",
  "F", "LValue", "Arguments", "ListExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-70)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -70,     7,    47,   -70,    -1,     8,    55,   -70,     2,    19,
      54,    24,    35,   -70,   -70,   -70,    72,   -70,    39,    72,
      19,    58,    52,   -70,    46,    60,   -70,    61,    71,     3,
     -70,   -70,    82,   -70,    62,    59,    65,    67,    41,    68,
     -70,   -70,   -70,   -70,    66,    77,    56,   -70,   -70,    79,
      56,    56,    73,   -70,   -70,    56,   -70,    56,    56,    10,
      83,    84,    86,    85,    78,   -70,   -70,    56,    23,    56,
     -70,    89,    62,    -7,    -5,    56,   -70,    -4,   -70,    56,
     -70,    56,    56,    56,    56,    56,    89,    80,    87,   -70,
      25,   -70,    30,    30,    81,   -70,    83,    84,    86,    85,
      78,   -70,    90,    56,   -70,    93,   -70,   -70,   -70,    89,
      30,   -70
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     2,     8,     0,     6,
       0,     0,     0,     7,    18,     9,     0,     3,     0,     0,
       0,    24,     0,    12,     0,    13,     5,     0,     0,     0,
      15,    10,     0,    11,    22,     0,     0,     0,     0,    53,
      33,    24,    16,    23,     0,     0,     0,    20,    17,     0,
       0,     0,    53,    49,    50,     0,    31,     0,     0,     0,
      35,    37,    39,    41,    43,    45,    51,    55,     0,     0,
      14,    21,    22,     0,     0,    55,    46,     0,    47,     0,
      30,     0,     0,     0,     0,     0,    57,     0,    54,    32,
       0,    19,     0,     0,     0,    48,    34,    36,    38,    40,
      42,    44,     0,     0,    25,    26,    28,    52,    29,    56,
       0,    27
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -70,   -70,   -70,   -70,   -70,    94,   -70,    91,   -70,   -70,
     -70,   -70,    32,    64,   -69,   -37,    27,    31,    26,    28,
      29,   -52,   -29,    40,   -70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    10,     6,     7,     8,    24,    25,    15,
      21,    35,    47,    29,    43,    86,    60,    61,    62,    63,
      64,    65,    66,    87,    88
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      44,    59,    79,    76,    79,    79,    78,     3,    36,    71,
      37,    38,     9,    73,    74,    92,    39,    93,    95,    79,
      77,    11,    40,   105,   106,    14,    41,    42,    36,    80,
      37,    38,    90,   101,    79,    36,    39,    37,    38,    44,
      16,   111,    40,    39,   104,    19,    41,    89,    20,    40,
       4,     5,    26,    41,    52,    53,    54,    55,    12,     5,
      56,    28,    57,    44,    44,    30,   109,    58,    31,    52,
      53,    54,    55,    17,    18,    22,    23,    57,    48,    49,
      32,    44,    58,    33,    34,    45,    50,    46,    51,    67,
      70,    69,    72,    81,    75,    85,    82,    83,    79,   110,
      13,    84,   102,   107,    91,    68,    96,   103,    98,   108,
      27,    99,    97,   100,     0,    94
};

static const yytype_int8 yycheck[] =
{
      29,    38,     9,    55,     9,     9,    58,     0,     5,    46,
       7,     8,    13,    50,    51,    22,    13,    22,    22,     9,
      57,    13,    19,    92,    93,    23,    23,    24,     5,    19,
       7,     8,    69,    85,     9,     5,    13,     7,     8,    68,
      21,   110,    19,    13,    19,    21,    23,    24,    13,    19,
       3,     4,    13,    23,    13,    14,    15,    16,     3,     4,
      19,     3,    21,    92,    93,    13,   103,    26,    22,    13,
      14,    15,    16,    19,    20,     3,     4,    21,    19,    20,
      20,   110,    26,    22,    13,     3,    21,    25,    21,    21,
      13,    25,    13,    10,    21,    17,    12,    11,     9,     6,
       6,    16,    22,    22,    72,    41,    79,    20,    82,    19,
      19,    83,    81,    84,    -1,    75
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    28,    29,     0,     3,     4,    31,    32,    33,    13,
      30,    13,     3,    32,    23,    36,    21,    19,    20,    21,
      13,    37,     3,     4,    34,    35,    13,    34,     3,    40,
      13,    22,    20,    22,    13,    38,     5,     7,     8,    13,
      19,    23,    24,    41,    49,     3,    25,    39,    19,    20,
      21,    21,    13,    14,    15,    16,    19,    21,    26,    42,
      43,    44,    45,    46,    47,    48,    49,    21,    40,    25,
      13,    42,    13,    42,    42,    21,    48,    42,    48,     9,
      19,    10,    12,    11,    16,    17,    42,    50,    51,    24,
      42,    39,    22,    22,    50,    22,    43,    44,    45,    46,
      47,    48,    22,    20,    19,    41,    41,    22,    19,    42,
       6,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    27,    28,    29,    29,    30,    30,    31,    31,    32,
      33,    33,    34,    34,    35,    35,    36,    37,    37,    38,
      38,    39,    39,    40,    40,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    42,    42,    43,    43,    44,    44,
      45,    45,    46,    46,    47,    47,    48,    48,    48,    48,
      48,    48,    48,    49,    50,    50,    51,    51
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     0,     3,     1,     2,     1,     2,
       5,     5,     1,     1,     4,     2,     4,     4,     0,     4,
       2,     2,     0,     2,     0,     4,     5,     7,     5,     5,
       3,     2,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     2,     2,     3,     1,
       1,     1,     4,     1,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* Prog: DeclarVarGlob DeclFoncts  */
#line 50 "src/tpcas.y"
                                {
                                    SymbolTable *table = NULL;
                                    (yyval.node) = makeNode(Prog);
                                    if (varGlob_flag){
                                        addChild((yyval.node), (yyvsp[-1].node));
                                        addSibling((yyvsp[-1].node), (yyvsp[0].node));
                                    } else {
                                        deleteTree((yyvsp[-1].node));
                                        addChild((yyval.node), (yyvsp[0].node));
                                    }
                                    // Construction table des symboles
                                    buildSymTables(&table, (yyval.node));
                                    if (tree_flag){
                                        printTree((yyval.node));
                                    }
                                    //printSymbolTable(table);
                                    // Construction code assembleur
                                    writeAsm(table);
                                    freeSymbolTable(&table);
                                    deleteTree((yyval.node));
                                }
#line 1224 "src/tpcas.tab.c"
    break;

  case 3: /* DeclarVarGlob: DeclarVarGlob TYPE DeclarateursGlob ';'  */
#line 73 "src/tpcas.y"
                                               {    
                                                    if (!varGlob_flag)
                                                        varGlob_flag = 1;
                                                    Node *child;
                                                    child = makeNode(Type);
                                                    child->name = strdup((yyvsp[-2].type));
                                                    addChild((yyvsp[-3].node), child);
                                                    addChild(child, (yyvsp[-1].node));
                                                }
#line 1238 "src/tpcas.tab.c"
    break;

  case 4: /* DeclarVarGlob: %empty  */
#line 82 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(DeclarVarGlob);
                                                }
#line 1246 "src/tpcas.tab.c"
    break;

  case 5: /* DeclarateursGlob: DeclarateursGlob ',' IDENT  */
#line 87 "src/tpcas.y"
                                                {               
                                                    Node * child = makeNode(Ident);
                                                    child->name = strdup((yyvsp[0].ident));
                                                    addSibling((yyvsp[-2].node), child);
                                                }
#line 1256 "src/tpcas.tab.c"
    break;

  case 6: /* DeclarateursGlob: IDENT  */
#line 92 "src/tpcas.y"
                                                {               
                                                    (yyval.node) = makeNode(Ident);
                                                    (yyval.node)->name = strdup((yyvsp[0].ident));
                                                }
#line 1265 "src/tpcas.tab.c"
    break;

  case 7: /* DeclFoncts: DeclFoncts DeclFonct  */
#line 98 "src/tpcas.y"
                                                {
                                                    (yyval.node) = (yyvsp[-1].node);
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1274 "src/tpcas.tab.c"
    break;

  case 8: /* DeclFoncts: DeclFonct  */
#line 102 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(DeclFoncts);
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1283 "src/tpcas.tab.c"
    break;

  case 9: /* DeclFonct: EnTeteFonct Corps  */
#line 108 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(DeclFonct);
                                                    addChild((yyval.node), (yyvsp[-1].node));
                                                    addSibling((yyvsp[-1].node), (yyvsp[0].node));
                                                }
#line 1293 "src/tpcas.tab.c"
    break;

  case 10: /* EnTeteFonct: TYPE IDENT '(' Parametres ')'  */
#line 115 "src/tpcas.y"
                                                {    

                                                    (yyval.node) = makeNode(EnTeteFonct);
                                                    Node *child1 , *child2;
                                                    child1 = makeNode(Type);
                                                    child1->name = strdup((yyvsp[-4].type));
                                                    addChild((yyval.node), child1);
                                                    child2 = makeNode(Ident);
                                                    child2->name = strdup((yyvsp[-3].ident));
                                                    addSibling(child1, child2);
                                                    addSibling(child2, (yyvsp[-1].node));
                                                }
#line 1310 "src/tpcas.tab.c"
    break;

  case 11: /* EnTeteFonct: VOID IDENT '(' Parametres ')'  */
#line 127 "src/tpcas.y"
                                                {   
                                                    (yyval.node) = makeNode(EnTeteFonct);
                                                    Node *child1, *child2;
                                                    child1 = makeNode(Type);
                                                    child1->name = strdup((yyvsp[-4].type));
                                                    child2 = makeNode(Ident);
                                                    addChild((yyval.node), child1);
                                                    child2->name = strdup((yyvsp[-3].ident));
                                                    addSibling(child1, child2);
                                                    addSibling(child2, (yyvsp[-1].node));
                                                }
#line 1326 "src/tpcas.tab.c"
    break;

  case 12: /* Parametres: VOID  */
#line 140 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Parametres);
                                                    Node *child = makeNode(Type);
                                                    child->name = strdup((yyvsp[0].type));
                                                    addChild((yyval.node), child);
                                                }
#line 1337 "src/tpcas.tab.c"
    break;

  case 13: /* Parametres: ListTypVar  */
#line 146 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Parametres);
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1346 "src/tpcas.tab.c"
    break;

  case 14: /* ListTypVar: ListTypVar ',' TYPE IDENT  */
#line 152 "src/tpcas.y"
                                                {
                                                    Node *child = makeNode(Type);
                                                    Node *child2 = makeNode(Ident);
                                                    child->name = strdup((yyvsp[-1].type));
                                                    child2->name = strdup((yyvsp[0].ident));
                                                    addSibling((yyvsp[-3].node), child);
                                                    addChild(child, child2);
                                                }
#line 1359 "src/tpcas.tab.c"
    break;

  case 15: /* ListTypVar: TYPE IDENT  */
#line 160 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Type);
                                                    Node *child = makeNode(Ident);
                                                    (yyval.node)->name = strdup((yyvsp[-1].type));
                                                    child->name = strdup((yyvsp[0].ident));
                                                    addChild((yyval.node), child);
                                                }
#line 1371 "src/tpcas.tab.c"
    break;

  case 16: /* Corps: '{' DeclarVarLoc SuiteInstr '}'  */
#line 168 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Corps);
                                                    if (varLoc_flag && suiteInstr_flag){
                                                        addChild((yyval.node), (yyvsp[-2].node));
                                                        addSibling((yyvsp[-2].node), (yyvsp[-1].node));
                                                    } else if (!varLoc_flag && suiteInstr_flag){
                                                        deleteTree((yyvsp[-2].node));
                                                        addChild((yyval.node), (yyvsp[-1].node));
                                                    } else if (varLoc_flag && !suiteInstr_flag){
                                                        deleteTree((yyvsp[-1].node));
                                                        addChild((yyval.node), (yyvsp[-2].node));
                                                    } else {
                                                        deleteTree((yyvsp[-2].node));
                                                        deleteTree((yyvsp[-1].node));
                                                        deleteTree((yyval.node));
                                                        (yyval.node) = NULL;
                                                    }
                                                }
#line 1394 "src/tpcas.tab.c"
    break;

  case 17: /* DeclarVarLoc: DeclarVarLoc TYPE DeclarateursLoc ';'  */
#line 188 "src/tpcas.y"
                                                {
                                                    if (!varLoc_flag)
                                                        varLoc_flag = 1;
                                                    Node *child;
                                                    child = makeNode(Type);
                                                    child->name = strdup((yyvsp[-2].type));
                                                    addChild((yyval.node), child);
                                                    addChild(child, (yyvsp[-1].node));
                                                }
#line 1408 "src/tpcas.tab.c"
    break;

  case 18: /* DeclarVarLoc: %empty  */
#line 197 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(DeclarVarLoc);
                                                }
#line 1416 "src/tpcas.tab.c"
    break;

  case 19: /* DeclarateursLoc: DeclarateursLoc ',' IDENT Affectation  */
#line 202 "src/tpcas.y"
                                                {
                                                    (yyval.node) = (yyvsp[-3].node);
                                                    if ((yyvsp[0].node)){
                                                        Node *tmp = (yyvsp[0].node)->firstChild;
                                                        Node *ident = makeNode(Ident);
                                                        ident->name = strdup((yyvsp[-1].ident));
                                                        addSibling(ident, tmp);
                                                        (yyvsp[0].node)->firstChild = ident;
                                                        addSibling((yyvsp[-3].node), (yyvsp[0].node));
                                                    } else {
                                                        Node *sibling = makeNode(Ident);
                                                        sibling->name = strdup((yyvsp[-1].ident));
                                                        addSibling((yyvsp[-3].node), sibling);
                                                        addChild(sibling, (yyvsp[0].node));
                                                    }
                                                    
                                                }
#line 1438 "src/tpcas.tab.c"
    break;

  case 20: /* DeclarateursLoc: IDENT Affectation  */
#line 219 "src/tpcas.y"
                                                {
                                                    if ((yyvsp[0].node)){
                                                        (yyval.node) = (yyvsp[0].node);
                                                        Node *tmp = (yyval.node)->firstChild;
                                                        Node *ident = makeNode(Ident);
                                                        ident->name = strdup((yyvsp[-1].ident));
                                                        addSibling(ident, tmp);
                                                        (yyval.node)->firstChild = ident;
                                                    } else {
                                                        (yyval.node) = makeNode(Ident);
                                                        (yyval.node)->name = strdup((yyvsp[-1].ident));
                                                        addChild((yyval.node), (yyvsp[0].node));
                                                    }
                                                }
#line 1457 "src/tpcas.tab.c"
    break;

  case 21: /* Affectation: '=' Exp  */
#line 235 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Assign);
                                                    (yyval.node)->name = strdup("=");
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1467 "src/tpcas.tab.c"
    break;

  case 22: /* Affectation: %empty  */
#line 240 "src/tpcas.y"
                                                {
                                                    (yyval.node) = NULL;
                                                }
#line 1475 "src/tpcas.tab.c"
    break;

  case 23: /* SuiteInstr: SuiteInstr Instr  */
#line 246 "src/tpcas.y"
                                                {
                                                    if (!suiteInstr_flag)
                                                        suiteInstr_flag = 1;
                                                    (yyval.node) = (yyvsp[-1].node);
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1486 "src/tpcas.tab.c"
    break;

  case 24: /* SuiteInstr: %empty  */
#line 252 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(SuiteInstr);
                                                }
#line 1494 "src/tpcas.tab.c"
    break;

  case 25: /* Instr: LValue '=' Exp ';'  */
#line 257 "src/tpcas.y"
                                                {   
                                                    (yyval.node) = makeNode(Assign);
                                                    (yyval.node)->name = strdup("=");
                                                    addChild((yyval.node), (yyvsp[-3].node));
                                                    addChild((yyval.node), (yyvsp[-1].node));
                                                }
#line 1505 "src/tpcas.tab.c"
    break;

  case 26: /* Instr: IF '(' Exp ')' Instr  */
#line 263 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(_if_);
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1515 "src/tpcas.tab.c"
    break;

  case 27: /* Instr: IF '(' Exp ')' Instr ELSE Instr  */
#line 268 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(_if_);
                                                    addChild((yyval.node), (yyvsp[-4].node));
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    Node *else__ = makeNode(_else_);
                                                    addSibling((yyval.node), else__);
                                                    addChild(else__, (yyvsp[0].node));
                                                }
#line 1528 "src/tpcas.tab.c"
    break;

  case 28: /* Instr: WHILE '(' Exp ')' Instr  */
#line 276 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(_while_);
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1538 "src/tpcas.tab.c"
    break;

  case 29: /* Instr: IDENT '(' Arguments ')' ';'  */
#line 281 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Ident);
                                                    (yyval.node)->name = strdup((yyvsp[-4].ident));
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                }
#line 1548 "src/tpcas.tab.c"
    break;

  case 30: /* Instr: RETURN Exp ';'  */
#line 286 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(_return_);
                                                    addChild((yyval.node), (yyvsp[-1].node));
                                                }
#line 1557 "src/tpcas.tab.c"
    break;

  case 31: /* Instr: RETURN ';'  */
#line 290 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(_return_);
                                                }
#line 1565 "src/tpcas.tab.c"
    break;

  case 32: /* Instr: '{' SuiteInstr '}'  */
#line 293 "src/tpcas.y"
                                                {
                                                    (yyval.node) = (yyvsp[-1].node);
                                                }
#line 1573 "src/tpcas.tab.c"
    break;

  case 33: /* Instr: ';'  */
#line 296 "src/tpcas.y"
                                                {
                                                    (yyval.node) = NULL;
                                                }
#line 1581 "src/tpcas.tab.c"
    break;

  case 34: /* Exp: Exp OR TB  */
#line 300 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(or);
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1591 "src/tpcas.tab.c"
    break;

  case 35: /* Exp: TB  */
#line 305 "src/tpcas.y"
                                                {
                                                    (yyval.node) = (yyvsp[0].node);
                                                }
#line 1599 "src/tpcas.tab.c"
    break;

  case 36: /* TB: TB AND FB  */
#line 309 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(and);
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1609 "src/tpcas.tab.c"
    break;

  case 37: /* TB: FB  */
#line 314 "src/tpcas.y"
                                                {
                                                    (yyval.node) = (yyvsp[0].node);
                                                }
#line 1617 "src/tpcas.tab.c"
    break;

  case 38: /* FB: FB EQ M  */
#line 318 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Eq);
                                                    (yyval.node)->name = strdup((yyvsp[-1].type));
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1628 "src/tpcas.tab.c"
    break;

  case 39: /* FB: M  */
#line 324 "src/tpcas.y"
                                                {
                                                    (yyval.node) = (yyvsp[0].node);
                                                }
#line 1636 "src/tpcas.tab.c"
    break;

  case 40: /* M: M ORDER E  */
#line 328 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Order);
                                                    (yyval.node)->name = strdup((yyvsp[-1].type));
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));                                                  
                                                }
#line 1647 "src/tpcas.tab.c"
    break;

  case 41: /* M: E  */
#line 335 "src/tpcas.y"
                                                {
                                                    (yyval.node) = (yyvsp[0].node);
                                                }
#line 1655 "src/tpcas.tab.c"
    break;

  case 42: /* E: E ADDSUB T  */
#line 339 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Addsub);
                                                    (yyval.node)->name = strdup((yyvsp[-1].byte));
                                                    addChild((yyval.node), (yyvsp[-2].node));
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1666 "src/tpcas.tab.c"
    break;

  case 43: /* E: T  */
#line 345 "src/tpcas.y"
                                                {
                                                    (yyval.node) = (yyvsp[0].node);
                                                }
#line 1674 "src/tpcas.tab.c"
    break;

  case 44: /* T: T DIVSTAR F  */
#line 349 "src/tpcas.y"
                   {
                                                    (yyval.node) = makeNode(Divstar); 
                                                    (yyval.node)->name = strdup((yyvsp[-1].byte));
                                                    addChild((yyval.node), (yyvsp[-2].node)); 
                                                    addChild((yyval.node), (yyvsp[0].node)); 
                                                }
#line 1685 "src/tpcas.tab.c"
    break;

  case 45: /* T: F  */
#line 355 "src/tpcas.y"
                                                {
                                                    (yyval.node) = (yyvsp[0].node);
                                                }
#line 1693 "src/tpcas.tab.c"
    break;

  case 46: /* F: ADDSUB F  */
#line 359 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(UnaryAddsub);
                                                    (yyval.node)->name = strdup((yyvsp[-1].byte));
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1703 "src/tpcas.tab.c"
    break;

  case 47: /* F: '!' F  */
#line 364 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(not);
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1712 "src/tpcas.tab.c"
    break;

  case 48: /* F: '(' Exp ')'  */
#line 368 "src/tpcas.y"
                                                {
                                                    (yyval.node) = (yyvsp[-1].node);
                                                }
#line 1720 "src/tpcas.tab.c"
    break;

  case 49: /* F: NUM  */
#line 371 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Num);
                                                    (yyval.node)->isnum = 1;
                                                    (yyval.node)->val = (yyvsp[0].num);
                                                }
#line 1730 "src/tpcas.tab.c"
    break;

  case 50: /* F: CHARACTER  */
#line 376 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Character);
                                                    (yyval.node)->name = strdup((yyvsp[0].byte)); 
                                                }
#line 1739 "src/tpcas.tab.c"
    break;

  case 51: /* F: LValue  */
#line 380 "src/tpcas.y"
                                                { 
                                                    (yyval.node) = (yyvsp[0].node);
                                                }
#line 1747 "src/tpcas.tab.c"
    break;

  case 52: /* F: IDENT '(' Arguments ')'  */
#line 383 "src/tpcas.y"
                                                {    
                                                    (yyval.node) = makeNode(Ident);
                                                    (yyval.node)->name = strdup((yyvsp[-3].ident));
                                                    addChild((yyval.node), (yyvsp[-1].node));
                                                }
#line 1757 "src/tpcas.tab.c"
    break;

  case 53: /* LValue: IDENT  */
#line 390 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Ident);
                                                    (yyval.node)->name = strdup((yyvsp[0].ident));
                                                }
#line 1766 "src/tpcas.tab.c"
    break;

  case 54: /* Arguments: ListExp  */
#line 396 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Arguments);
                                                    addChild((yyval.node), (yyvsp[0].node));
                                                }
#line 1775 "src/tpcas.tab.c"
    break;

  case 55: /* Arguments: %empty  */
#line 400 "src/tpcas.y"
                                                {
                                                    (yyval.node) = makeNode(Arguments);
                                                    addChild((yyval.node), makeNode(Type));
                                                }
#line 1784 "src/tpcas.tab.c"
    break;

  case 56: /* ListExp: ListExp ',' Exp  */
#line 406 "src/tpcas.y"
                                                { 
                                                    addSibling((yyvsp[-2].node), (yyvsp[0].node));
                                                }
#line 1792 "src/tpcas.tab.c"
    break;

  case 57: /* ListExp: Exp  */
#line 409 "src/tpcas.y"
                                                { 
                                                    (yyval.node) = (yyvsp[0].node); 
                                                }
#line 1800 "src/tpcas.tab.c"
    break;


#line 1804 "src/tpcas.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 413 "src/tpcas.y"


int yyerror(char *msg){
    fprintf(stderr, "Parse error in line %d, near column %d\n%s\n", 
            lineno, errorinline, msg);
    return 0;
}

int main(int argc, char *argv[]){
    if (read_option(argc, argv) == 1){
        fprintf(stderr, "option do not exists\n");
        return 2;
    }
    if (help_flag){
        print_synopsis();
        return 2;
    }
    if (argc > 1 && !last_is_option(argc, argv)){
        freopen(argv[argc - 1], "r", stdin);
    }
    return yyparse();
}