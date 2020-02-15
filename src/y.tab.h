/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    tIntVal = 258,
    tFloatVal = 259,
    tIdentifier = 260,
    tStringVal = 261,
    tVar = 262,
    tString = 263,
    tElse = 264,
    tPrint = 265,
    tFloat = 266,
    tBool = 267,
    tWhile = 268,
    tTrue = 269,
    tInt = 270,
    tIf = 271,
    tRead = 272,
    tFalse = 273,
    tPlus = 274,
    tMinus = 275,
    tNot = 276,
    tTime = 277,
    tDivide = 278,
    tAssign = 279,
    tEqual = 280,
    tNotEqual = 281,
    tGreaterEqual = 282,
    tLessEqual = 283,
    tGreaterThan = 284,
    tLessThan = 285,
    tAnd = 286,
    tOr = 287,
    tLeftParen = 288,
    tRightParen = 289,
    tLeftCurly = 290,
    tRightCurly = 291,
    tSemicolon = 292,
    tColon = 293,
    UMINUS = 294,
    NOT = 295
  };
#endif
/* Tokens.  */
#define tIntVal 258
#define tFloatVal 259
#define tIdentifier 260
#define tStringVal 261
#define tVar 262
#define tString 263
#define tElse 264
#define tPrint 265
#define tFloat 266
#define tBool 267
#define tWhile 268
#define tTrue 269
#define tInt 270
#define tIf 271
#define tRead 272
#define tFalse 273
#define tPlus 274
#define tMinus 275
#define tNot 276
#define tTime 277
#define tDivide 278
#define tAssign 279
#define tEqual 280
#define tNotEqual 281
#define tGreaterEqual 282
#define tLessEqual 283
#define tGreaterThan 284
#define tLessThan 285
#define tAnd 286
#define tOr 287
#define tLeftParen 288
#define tRightParen 289
#define tLeftCurly 290
#define tRightCurly 291
#define tSemicolon 292
#define tColon 293
#define UMINUS 294
#define NOT 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "mini.y" /* yacc.c:1909  */

	int intVal;
	float floatVal;
	char *stringVal;
	struct PROG *prog;
	struct EXP *exp;
	struct STMT *stmt;
	

#line 144 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
