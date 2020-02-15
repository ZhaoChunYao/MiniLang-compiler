%{
	#include<stdlib.h>
	#include<stdio.h>
	#include<string.h>
	#include"y.tab.h"
	extern char *mode;
	extern int lineno;

	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

%}

DIGIT [0-9]
%option yylineno


%%
[\r\n]+	
[ \t]+  
"#"[^\n]*"\n"
"+"	{
		if(strcmp(mode,"tokens")==0){printf("%s\n","tPlus");}
		return tPlus;
	}
"-"	{
		if(strcmp(mode,"tokens")==0){printf("%s\n","tMinus");}
		return tMinus;
	}

"!"	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tMinus");}
                return tNot;
        }

"*"	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tTime");}
		return tTime;
        }
"/"	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tDivde");}
		return tDivide;
        }
"=="	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tAssign");}
		return tEqual;
        }
"!=" 	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tNotEqual");}
		return tNotEqual;
        }

">="    {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tLessEqual");}
		return tLessEqual;
        }
"<="    {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tGreaterEqual");}
		return tGreaterEqual;
        }
">"    {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tGreaterThan");}
		return tGreaterThan;
        }
"<"    {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tLessThan");}
		return tLessThan;
        }
"&&"    {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tAnd");}
      		return tAnd;
	 }
"||"    {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tOr");}
		return tOr;

        }
";"    {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tSemicolon");}
		return tSemicolon;
        }
":"    {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tColon");}
                return tColon;
        }
"("    {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tLeftParen");}
		return tLeftParen;
        }
")"    {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tRightParen");}
		return tRightParen;
      	}
"{"    {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tLeftCurly");}
		return tLeftCurly;
    	}
"}"	{	
                if(strcmp(mode,"tokens")==0){printf("%s\n","tRightCurly");}
		return tRightCurly;
        } 
"="     {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tAssign");}
                return tAssign;
        }
var   	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tVar");}
		return tVar;
        }
else  	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tElse");}
                return tElse;
        }
print  	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tPrint");}
                return tPrint;
	}
while   {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tWhile");}
                return tWhile;
        }
True  	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tTrue");}
		yylval.stringVal = strdup(yytext);
                return tTrue;
        }
False   {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tFalse");}
		yylval.stringVal = strdup(yytext);
                return tFalse;
        }
read  	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tRead");}
                return tRead;
        }
if   	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tIf");}
                return tIf;
        }
string  {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tString");}
		yylval.stringVal = strdup(yytext);
                return tString;
        }
float   {
                if(strcmp(mode,"tokens")==0){printf("%s\n","tFloat");}
		yylval.stringVal = strdup(yytext);
                return tFloat;
        }
bool   	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tBool");}
		yylval.stringVal = strdup(yytext);
                return tBool;
        }
int   	{
                if(strcmp(mode,"tokens")==0){printf("%s\n","tInt");}
		yylval.stringVal = strdup(yytext);
                return tInt;
        }

0|([1-9]{DIGIT}*)	{
            	if(strcmp(mode,"tokens")==0){printf("tIntVal(%s)\n",yytext);}
		yylval.intVal = atoi(yytext);
		return tIntVal;
        }
(0|([1-9]{DIGIT}*))"."{DIGIT}*       {
                if(strcmp(mode,"tokens")==0){printf("tFloatVal(%s)\n",yytext);}
                yylval.floatVal = atof(yytext);
                return tFloatVal;
                
        }
[a-zA-Z_][a-zA-Z0-9_]*   	{
                if(strcmp(mode,"tokens")==0){printf("tIdentifier(%s)\n",yytext);}
                yylval.stringVal = strdup(yytext);
                return tIdentifier;
        }
\"([^"]*)\" {
                if(strcmp(mode,"tokens")==0){printf("tStringVal(%s)\n",yytext);}
                yylval.stringVal = strdup(yytext);
                return tStringVal;
        }
.       {
                fprintf(stderr, "Error: (line %d) unexpected char '%s'\n",
                                yylineno, yytext);
                exit(1);
        }






%%
