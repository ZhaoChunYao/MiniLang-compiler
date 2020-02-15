#include<stdio.h>
#include"pretty.h"

void prettyEXP(EXP *e)
{
	switch(e->kind)
	{
		case identifier:
			printf("%s",e->val.idE.identifier);
			break;
		case intLiteral:
			printf("%i",e->val.intLiteral);
			break;
		case floatLiteral:
			printf("%f",e->val.floatLiteral);
			break;
		case stringLiteral:
                        printf("%s",e->val.stringLiteral);
                        break;
		case boolLiteral:
                        printf("%s",e->val.boolLiteral);
                        break;
		case addition:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("+");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case subtraction:
                        printf("(");
                        prettyEXP(e->val.binary.lhs);
                        printf("-");
                        prettyEXP(e->val.binary.rhs);
                        printf(")");
                        break;
		case multiplication:
                        printf("(");
                        prettyEXP(e->val.binary.lhs);
                        printf("*");
                        prettyEXP(e->val.binary.rhs);
                        printf(")");
                        break;
		case division:
                        printf("(");
                        prettyEXP(e->val.binary.lhs);
                        printf("/");
                        prettyEXP(e->val.binary.rhs);
                        printf(")");
                        break;
		case equals:
                        printf("(");
                        prettyEXP(e->val.binary.lhs);
                        printf("==");
                        prettyEXP(e->val.binary.rhs);
                        printf(")");
                        break;
		case notEqual:
                        printf("(");
                        prettyEXP(e->val.binary.lhs);
                        printf("!=");
                        prettyEXP(e->val.binary.rhs);
                        printf(")");
                        break;
		case greaterEqual:
                        printf("(");
                        prettyEXP(e->val.binary.lhs);
                        printf(">=");
                        prettyEXP(e->val.binary.rhs);
                        printf(")");
                        break;
		case lessEqual:
                        printf("(");
                        prettyEXP(e->val.binary.lhs);
                        printf("<=");
                        prettyEXP(e->val.binary.rhs);
                        printf(")");
                        break;
		case greaterThan:
                        printf("(");
                        prettyEXP(e->val.binary.lhs);
                        printf(">");
                        prettyEXP(e->val.binary.rhs);
                        printf(")");
                        break;
		case lessThan:
                        printf("(");
                        prettyEXP(e->val.binary.lhs);
                        printf("<");
                        prettyEXP(e->val.binary.rhs);
                        printf(")");
                        break;
		case expressionKindAnd:
                        printf("(");
                        prettyEXP(e->val.binary.lhs);
                        printf("&&");
                        prettyEXP(e->val.binary.rhs);
                        printf(")");
                        break;
		case expressionKindOr:
                        printf("(");
                        prettyEXP(e->val.binary.lhs);
                        printf("||");
                        prettyEXP(e->val.binary.rhs);
                        printf(")");
                        break;
		case expressionKindNot:
                        printf("!(");
                        prettyEXP(e->val.exp);
                        printf(")");
                        break;
		case minus:
                        printf("-(");
                        prettyEXP(e->val.exp);
                        printf(")");
                        break;
	}
}

void prettySTMT(STMT *s)
{
	if(s==NULL){return;}
	prettySTMT(s->next);
	switch(s->kind)
	{
		case read: 
			printf("%s","read(");
			prettyEXP(s->val.identifier);
			printf("%s",");\n");
			break;
		case print:
			printf("%s","print(");
                        prettyEXP(s->val.exp);
                        printf("%s",");\n");
                        break;
		case assignment:
                        prettyEXP(s->val.assignment.identifier);
                        printf("%s","=");
			prettyEXP(s->val.assignment.rhs);
			printf("%s",";\n");
                        break;
		case statementKindIf:
			printf("%s","if(");
                        prettyEXP(s->val.ifStatement.condition);
                        printf("%s","){\n");
                        prettySTMT(s->val.ifStatement.ifBody);
			printf("%s","}");
			if(s->val.ifStatement.elseBody==NULL){printf("\n%s\n","ELSE BODY ERROR"); break;}
			else
			{
				printf("%s","else{\n");
				prettySTMT(s->val.ifStatement.elseBody);
				printf("%s","}\n");
			}
                        break;
		case statementKindWhile:
			printf("%s","while(");
                        prettyEXP(s->val.whileLoop.condition);
                        printf("%s","){\n");
                        prettySTMT(s->val.whileLoop.body);
			printf("%s","}\n");
			break;
		case declaration:
			printf("%s","var ");
			prettyEXP(s->val.declaration.identifier);
                        printf("%s","=");
                        prettyEXP(s->val.declaration.rhs);
			printf("%s",";\n");
                        break;
	}
}


void prettyPROG(PROG *root)
{
	printf("%s","start\n");
	prettySTMT(root->head);
}
