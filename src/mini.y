%{
#include<stdio.h>
#include<stdlib.h>
#include"tree.h"

extern int yylineno;
int yylex();

void yyerror(const char *s){
	fprintf(stderr,"Error: (line %d) %s\n",yylineno,s);
	exit(1);
	}	
extern PROG *root;
%}

%union{
	int intVal;
	float floatVal;
	char *stringVal;
	struct PROG *prog;
	struct EXP *exp;
	struct STMT *stmt;
	
}

%type <exp> expression;
%type <exp> type;
%type <stmt> declaration;
/*%type <stmt> ifStatement;*/
%type <stmt> statement;
%type <stmt> statements;
%type <prog> program;
%token <intVal> tIntVal;
%token <floatVal> tFloatVal;
%token <stringVal> tIdentifier;
%token <stringVal> tStringVal;
%token tVar;
%token <stringVal> tString;
%token tElse;
%token tPrint;
%token <stringVal> tFloat;
%token <stringVal> tBool;
%token tWhile;
%token <stringVal> tTrue;
%token <stringVal> tInt;
%token tIf;
%token tRead;
%token <stringVal> tFalse;
%token tPlus;
%token tMinus;
%token tNot
%token tTime;
%token tDivide;
%token tAssign;
%token tEqual;
%token tNotEqual;
%token tGreaterEqual;
%token tLessEqual;
%token tGreaterThan;
%token tLessThan;
%token tAnd;
%token tOr;
%token tLeftParen;
%token tRightParen;
%token tLeftCurly;
%token tRightCurly;
%token tSemicolon;
%token tColon;

%left tAnd tOr
%left tEqual tNotEqual tGreaterEqual tLessEqual tGreaterThan tLessThan
%left tPlus tMinus
%left tTime tDivide
%left tLeftParen tRightParen
%left UMINUS NOT

%start program

%locations
%error-verbose

%%
program: statements {$$=makePROG($1); root=$$;printf("%s","reach0");} /*$1是statements的最后一个$$*/
;

statements: %empty {$$=NULL; printf("%s","reach1");}
    |statements statement {$$=$2;$$->next=$1; printf("%s","reach2");} /*最后一个statement：$$=它自己，next是剩下的整个llist*/
;
statement: tRead tLeftParen expression tRightParen tSemicolon {$$=makeSTMT_read($3); printf("%s","reach3");}
         |tPrint tLeftParen expression tRightParen tSemicolon {$$=makeSTMT_print($3); printf("%s","reach4");}
         |expression tAssign expression tSemicolon {$$=makeSTMT_assignment($1,$3); printf("%s","reach5");}
	 |tIf tLeftParen expression tRightParen tLeftCurly statements tRightCurly {$$=makeSTMT_if($3,$6,NULL); printf("%s","reach6");}
         |tIf tLeftParen expression tRightParen tLeftCurly statements tRightCurly tElse tLeftCurly statements tRightCurly {$$=makeSTMT_if($3,$6,$10); printf("%s","reach7");}
         |tIf tLeftParen expression tRightParen tLeftCurly statements tRightCurly tElse statement {$$=makeSTMT_if($3,$6,$9); printf("%s","reach8");} /*接
下来是只match statement吗? statement会成为指向这一个node的node吗？*/
         |tWhile tLeftParen expression tRightParen tLeftCurly statements tRightCurly {$$=makeSTMT_while($3,$6); printf("%s","reach9");}
	 |declaration {$$=$1; printf("%s","reach10");}
;
/*ifStatement: tIf tLeftParen expression tRightParen tLeftCurly statements tRightCurly {$$=makeSTMT_if($3,$6,NULL); printf("%s","reach6");}
	   |tIf tLeftParen expression tRightParen tLeftCurly statements tRightCurly tElse tLeftCurly statements tRightCurly {$$=makeSTMT_if($3,$6,$10); printf("%s","reach7");}
	   |tIf tLeftParen expression tRightParen tLeftCurly statements tRightCurly tElse ifStatement {$$=makeSTMT_if($3,$6,$9); printf("%s","reach8");} /*接下来是只match statement吗? statement会成为指向这一个node的node吗？*/

declaration: tVar expression tColon type tAssign expression tSemicolon {$$=makeSTMT_declaration($2,$4,$6); printf("%s","reach11");}
	  | tVar expression tAssign expression tSemicolon {$$=makeSTMT_declaration($2,NULL,$4); printf("%s","reach12");}
;
type: tInt {$$=makeEXP_type($1);}
    |tFloat {$$=makeEXP_type($1);}
    |tBool {$$=makeEXP_type($1);}
    |tString {$$=makeEXP_type($1);}
;
expression: expression tOr expression {$$=makeEXP_or($1,$3); printf("%s","reach13");}
	  |expression tAnd expression {$$=makeEXP_and($1,$3); printf("%s","reach14");}
	  |expression tEqual expression {$$=makeEXP_equals($1,$3); printf("%s","reach16");}
	  |expression tNotEqual expression {$$=makeEXP_notEqual($1,$3); printf("%s","reach17");}
	  |expression tGreaterEqual expression {$$=makeEXP_greaterEqual($1,$3); printf("%s","reach18");}
	  |expression tLessEqual expression {$$=makeEXP_lessEqual($1,$3); printf("%s","reach19");}
	  |expression tGreaterThan expression {$$=makeEXP_greaterThan($1,$3); printf("%s","reach20");}
	  |expression tLessThan expression {$$=makeEXP_lessThan($1,$3); printf("%s","reach21");}
	  |expression tPlus expression {$$=makeEXP_addition($1,$3); printf("%s","reach22");}
	  |expression tMinus expression {$$=makeEXP_subtraction($1,$3); printf("%s","reach23");}
	  |expression tTime expression {$$=makeEXP_multiplication($1,$3); printf("%s","reach24");}
	  |expression tDivide expression {$$=makeEXP_division($1,$3); printf("%s","reach25");}
	  |tMinus expression %prec UMINUS {$$=makeEXP_minus($2); printf("%s","reach26");}
	  |tNot expression %prec NOT {$$=makeEXP_not($2); printf("%s","reach27");}
	  |tLeftParen expression tRightParen {$$=$2; printf("%s","reach28");}
	  |tTrue {$$=makeEXP_boolLiteral($1); printf("%s","reach29");}
	  |tFalse {$$=makeEXP_boolLiteral($1); printf("%s","reach30");}
	  |tIntVal {$$=makeEXP_intLiteral($1); printf("%s","reach31");}
	  |tFloatVal {$$=makeEXP_floatLiteral($1); printf("%s","reach32");}
	  |tStringVal {$$=makeEXP_stringLiteral($1); printf("%s","reach33");}
	  |tIdentifier {$$=makeEXP_identifier($1,yylineno); printf("%s","reach34");}

%%








