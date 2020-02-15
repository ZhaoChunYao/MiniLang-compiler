#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
SymbolKind checkEXP(EXP *e)
{
	//printf("\n%s%d\n","EXPKind: ",e->kind);
        switch(e->kind)
        {
                case identifier:
			if(e->val.idE.idSym==NULL){printf("\n%s%s\n",e->val.idE.identifier,"NULL!");break;}
			return e->val.idE.idSym->kind;
                case stringLiteral:
			if(strcmp(e->val.stringLiteral,"True")==0||strcmp(e->val.stringLiteral,"False")==0){return k_bool;}
			return k_string;
		case boolLiteral:
			return k_bool;
                case intLiteral:
			return k_int;
                case floatLiteral:
			return k_float;
                case addition:
			{
				;
				SymbolKind lhsType=checkEXP(e->val.binary.lhs);
				SymbolKind rhsType=checkEXP(e->val.binary.rhs);
				if(lhsType==k_int&&rhsType==k_int){return k_int;}
				if(lhsType==k_float&&rhsType==k_float){return k_float;}
				if(lhsType==k_string&&rhsType==k_string){return k_string;}
				if((lhsType==k_float&&rhsType==k_int)||(lhsType==k_int&&rhsType==k_float)){return k_float;}
				printf("\n%s%s%s%s\n","Type Error: cannot add ",getType(lhsType)," to ",getType(rhsType)); 
				exit(1);
				
			}
		case subtraction:
                case multiplication:
                case division:
                        {
                                ;
                                SymbolKind lhsType=checkEXP(e->val.binary.lhs);
                                SymbolKind rhsType=checkEXP(e->val.binary.rhs);
                                if(lhsType==k_int&&rhsType==k_int){return k_int;}
                                if(lhsType==k_float&&rhsType==k_float){return k_float;}
                                if((lhsType==k_float&&rhsType==k_int)||(lhsType==k_int&&rhsType==k_float)){return k_float;}
                                printf("\n%s%s%s%s\n","Type Error: cannot do math operation between ",getType(lhsType)," and ",getType(rhsType));
                                exit(1);
                        }

                case expressionKindAnd:
                case expressionKindOr:
			{
                                ;
                                SymbolKind lhsType=checkEXP(e->val.binary.lhs);
                                SymbolKind rhsType=checkEXP(e->val.binary.rhs);
                                if(lhsType==k_bool&&rhsType==k_bool){return k_bool;}
                                printf("\n%s%s%s%s\n","Type Error: cannot do logical operation between ",getType(lhsType)," and ",getType(rhsType));
                                exit(1);
                        }

                case equals:
                case notEqual:
                case greaterEqual:
                case lessEqual:
		case greaterThan:
		case lessThan:
			{
                                ;
                                SymbolKind lhsType=checkEXP(e->val.binary.lhs);
                                SymbolKind rhsType=checkEXP(e->val.binary.rhs);
                                if(lhsType==k_int&&rhsType==k_int){return k_bool;}
                                if(lhsType==k_float&&rhsType==k_float){return k_bool;}
				if(lhsType==k_string&&rhsType==k_string){return k_bool;}
                                if((lhsType==k_float&&rhsType==k_int)||(lhsType==k_int&&rhsType==k_float)){return k_bool;}
                                printf("\n%s%s%s%s\n","Type Error: cannot compare ",getType(lhsType)," with ",getType(rhsType));
                                exit(1);
                        }

                case minus:
			{
				;
				SymbolKind expType=checkEXP(e->val.exp);
				if(expType==k_int){return k_int;}
				if(expType==k_float){return k_float;}
				printf("\n%s%s\n","Type Error: cannot mathametically negate ",getType(expType));
			}
                case expressionKindNot:
			{
				;
                                SymbolKind expType=checkEXP(e->val.exp);
                                if(expType==k_bool){return k_bool;}
                                printf("\n%s%s\n","Type Error: cannot logically negate ",getType(expType));
                        }
        }
}

void checkSTMT(STMT *s)
{
        if(s==NULL){return;}
        checkSTMT(s->next);
	//printf("\n%s%d\n","STMT Kind: ",s->kind);
        switch(s->kind)
        {
                case read:
			//printf("\n%s","arrivedRead!!!!");
                        break;
                case print:
			//printf("\n%s","arrivedPrint!!!!");
                        checkEXP(s->val.exp);
                        break;
                case assignment:
			//printf("\n%s","arrivedAss!!!!");
			{	
				;
				SymbolKind idType=checkEXP(s->val.assignment.identifier);
				SymbolKind rhsType=checkEXP(s->val.assignment.rhs);
				if(idType==k_unknown){s->val.assignment.identifier->val.idE.idSym->kind=rhsType;}
				else if(idType==rhsType){break;}
				else if(idType==k_float&&rhsType==k_int){break;}
				else{printf("\n%s%s%s%s\n","Type Error: cannot assign ",getType(rhsType)," to ",getType(idType)); exit(1);}
                        	break;
			}
                case statementKindIf:
                        {
				//printf("\n%s","arrivedIf!!!!");
                                SymbolKind conditionType=checkEXP(s->val.ifStatement.condition);
				if(conditionType!=k_bool){printf("\n%s\n","Type Error: if condition must be bool."); exit(1);}
                               	checkSTMT(s->val.ifStatement.ifBody);
                                checkSTMT(s->val.ifStatement.elseBody);
                                break;
                        }
                case statementKindWhile:
                        {
				//printf("\n%s","arrivedWhile!!!!");
				SymbolKind conditionType=checkEXP(s->val.whileLoop.condition);
                                if(conditionType!=k_bool){printf("\n%s\n","Type Error: while condition must be bool."); exit(1);}
                                checkSTMT(s->val.whileLoop.body);
                                break;

                        }

                case declaration:
			{
				;
				SymbolKind idType=checkEXP(s->val.declaration.identifier);
				SymbolKind rhsType=checkEXP(s->val.declaration.rhs);
				//printf("%d%d\t",idType,rhsType);
				if(idType==k_unknown){s->val.assignment.identifier->val.idE.idSym->kind=rhsType;} /*STMT.EXP.SYMBOL.kind*/
                                else if(idType==rhsType){break;}
                                else if(idType==k_float&&rhsType==k_int){break;}
                                else{printf("\n%s%s%s%s\n","Type Error: cannot assign ",getType(rhsType)," to ",getType(idType)); exit(1);}
                                break;

			}
        }
}

void checkPROG(PROG *root)
{
        if(root==NULL){return;}
	checkSTMT(root->head);
}



