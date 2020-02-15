#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codeGen.h"

int indentation=0;
void indent(int identation,FILE *fp)
{
        for(int i=0;i<indentation;i++)
        {
                fputs("\t",fp);
        }
}

void genEXP(EXP *e,FILE *fp)
{
        switch(e->kind)
        {
                case identifier:
			fputs(e->val.idE.identifier,fp);
			break;
		case boolLiteral:
			fputs("\"",fp);
                        fputs(e->val.boolLiteral,fp);
			fputs("\"",fp);
                        break;
                case stringLiteral:
			fputs(e->val.stringLiteral,fp);
			break;
                case intLiteral:
			fprintf(fp,"%d",e->val.intLiteral);//stream, format specifiers, arguments replacing the specifiers
			break;
                case floatLiteral:
			fprintf(fp,"%f",e->val.floatLiteral);
			break;
                case addition:
			{
				;
				SymbolKind lhsType=checkEXP(e->val.binary.lhs);
				SymbolKind rhsType=checkEXP(e->val.binary.rhs);
				if(lhsType==k_string&&rhsType==k_string)
				{
					fputs("strAdd(",fp);
					genEXP(e->val.binary.lhs,fp);
					fputs(",",fp);
					genEXP(e->val.binary.rhs,fp);
					fputs(")",fp);
				}
				else
				{
					genEXP(e->val.binary.lhs,fp);
                                	fputs("+",fp);
                                	genEXP(e->val.binary.rhs,fp);
				}
			}
			break;
		case subtraction:
			genEXP(e->val.binary.lhs,fp);
                        fputs("-",fp);
                        genEXP(e->val.binary.rhs,fp);
			break;
                case multiplication:
			genEXP(e->val.binary.lhs,fp);
                        fputs("*",fp);
                        genEXP(e->val.binary.rhs,fp);
			break;
                case division:
                        {
                                ;
				genEXP(e->val.binary.lhs,fp);
                                fputs("/",fp);
                                genEXP(e->val.binary.rhs,fp);
                        }
			break;
                case expressionKindAnd:
			genEXP(e->val.binary.lhs,fp);
                        fputs("&&",fp);
                        genEXP(e->val.binary.rhs,fp);
			break;
                case expressionKindOr:
			{
                                ;
				genEXP(e->val.binary.lhs,fp);
                        	fputs("||",fp);
                        	genEXP(e->val.binary.rhs,fp);
                        }
			break;
                case equals:
			genEXP(e->val.binary.lhs,fp);
                        fputs("==",fp);
                        genEXP(e->val.binary.rhs,fp);
			break;
                case notEqual:
			genEXP(e->val.binary.lhs,fp);
                        fputs("!=",fp);
                        genEXP(e->val.binary.rhs,fp);
			break;
                case greaterEqual:
			genEXP(e->val.binary.lhs,fp);
                        fputs(">=",fp);
                        genEXP(e->val.binary.rhs,fp);
			break;
                case lessEqual:
			genEXP(e->val.binary.lhs,fp);
                        fputs("<=",fp);
                        genEXP(e->val.binary.rhs,fp);
			break;
		case greaterThan:
			genEXP(e->val.binary.lhs,fp);
                        fputs(">",fp);
                        genEXP(e->val.binary.rhs,fp);
			break;
		case lessThan:
			{
                                ;
				genEXP(e->val.binary.lhs,fp);
                        	fputs("<",fp);
                        	genEXP(e->val.binary.rhs,fp);
                        }
			break;
                case minus:
			{
				;
				fputs("-(",fp);
				genEXP(e->val.exp,fp);
				fputs(")",fp);
			}
			break;
                case expressionKindNot:
			{
				;
				fputs("!(",fp);
                                genEXP(e->val.exp,fp);
                                fputs(")",fp);
                        }
			break;
        }
}

void genSTMT(STMT *s,FILE *fp)
{
        if(s==NULL){return;}
        genSTMT(s->next,fp);
        switch(s->kind)
        {
                case read:
			indent(indentation,fp);
			fputs("scanf(\"",fp);
			SymbolKind k=checkEXP(s->val.identifier);
                                switch(k)
                                {
                                        case k_int:
                                                fputs("\%d\",&",fp);
						genEXP(s->val.identifier,fp);
                        			fputs(");\n",fp);
                                                break;
                                        case k_float:
                                                fputs("\%f\",&",fp);
						genEXP(s->val.identifier,fp);
                        			fputs(");\n",fp);
                                                break;
					case k_bool:
                                        case k_string:
                                                fputs("\%s\",scanBuffer);\n",fp);
						indent(indentation,fp);
						genEXP(s->val.identifier,fp);
						fputs("=strdup(scanBuffer);\n",fp);
                                                break;

						
                                }
				break;
                case print:
			{
				indent(indentation,fp);
				fputs("printf(\"",fp);
				SymbolKind k=checkEXP(s->val.exp);
				switch(k)
				{
					case k_int:
						fputs("\%d\",",fp);
						break;
					case k_float:
						fputs("\%f\",",fp);
						break;
					case k_bool:
						printf("reached2!");
						fputs("\%s\",",fp);
						break;
					case k_string:
						fputs("\%s\",",fp);
						break; 
				}
				genEXP(s->val.exp,fp);
                                fputs(");\n",fp);
				break;
			}
                case assignment:
			{	
				;
				indent(indentation,fp);
				genEXP(s->val.assignment.identifier,fp);
				fputs("=",fp);
				genEXP(s->val.assignment.rhs,fp);
				fputs(";\n",fp);
                        	break;
			}
                case statementKindIf:
                        {
				indent(indentation,fp);
				fputs("if(",fp);
                                genEXP(s->val.ifStatement.condition,fp);
				fputs("){\n",fp);
				indentation++;
                               	genSTMT(s->val.ifStatement.ifBody,fp);
				indentation--;
				fputs("\n",fp);
				indent(indentation,fp);
				fputs("}\n",fp);
				if(s->val.ifStatement.elseBody!=NULL)
				{
					indent(indentation,fp);
					fputs("else{\n",fp);
					indentation++;
					genSTMT(s->val.ifStatement.elseBody,fp);
					fputs("\n",fp);
					indentation--;
					indent(indentation,fp);
					fputs("}\n",fp);
				}
                                break;
                        }
                case statementKindWhile:
                        {
				indent(indentation,fp);
				fputs("while(",fp);
				genEXP(s->val.whileLoop.condition,fp);
				fputs("){\n",fp);
				indentation++;
                                genSTMT(s->val.whileLoop.body,fp);
				indentation--;
				fputs("\n",fp);
				indent(indentation,fp);
				fputs("}\n",fp);
                                break;

                        }

                case declaration:
			{
				;
				indent(indentation,fp);
				SymbolKind k=checkEXP(s->val.declaration.identifier);
				switch(k)
                                {
                                        case k_int:
                                                fputs("int ",fp);
                                                break;
                                        case k_float:
                                                fputs("float ",fp);
                                                break;
                                        case k_string:
                                                fputs("char *",fp);
                                                break;
                                }
				genEXP(s->val.declaration.identifier,fp);
				fputs("=",fp);
				genEXP(s->val.declaration.rhs,fp);
				fputs(";\n",fp);
                                break;

			}
        }
}

void genPROG(PROG *root,char *filename)
{
	FILE *fp=fopen(filename,"w");
	fputs("#include<stdio.h>\n#include<stdlib.h>\n#include<stdbool.h>\n#include<string.h>\n\nchar scanBuffer[1024];\n\n",fp);
	char *helperFunction="char *strAdd(char *str1,char *str2){\n\tchar *buffer=malloc (sizeof (char) * 1024);\n\tint pos=0;\n\tfor(int i=0;i<strlen(str1);i++){\n\t\tbuffer[i]=str1[i];\n\t\tpos=i;\n\t}\n\tfor(int i=0;i<strlen(str2);i++){\n\t\tbuffer[pos+1+i]=str2[i];\n\t}\n\treturn buffer;\n}\n\n";
        fputs(helperFunction,fp);
	fputs("int main()\n{\n",fp);
	indentation++;
        if(root==NULL){return;}
	genSTMT(root->head,fp);
	fputs("}",fp);
	fclose(fp);
}
