#include"tree.h"
#include<stdlib.h>
#include"string.h"
EXP * makeEXP_identifier(char *varName,int lineno)
{
        EXP *e=malloc(sizeof(EXP));
	e->val.idE.lineno=lineno;
        e->kind=identifier;
        e->val.idE.identifier=varName;
	e->val.idE.idSym;
        return e;
}

EXP * makeEXP_boolLiteral(char *string)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=boolLiteral;
        e->val.boolLiteral=string;
        return e;
}


EXP * makeEXP_stringLiteral(char *string)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=stringLiteral;
        e->val.stringLiteral=string;
        return e;
}

EXP * makeEXP_intLiteral(int data)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=intLiteral;
        e->val.intLiteral=data;
        return e;
}

EXP * makeEXP_floatLiteral(float data)
{
	EXP *e=malloc(sizeof(EXP));
	e->kind=floatLiteral;
	e->val.floatLiteral=data;
	return e;
}

EXP * makeEXP_addition(EXP *lhs,EXP *rhs)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=addition;
        e->val.binary.lhs=lhs;
	e->val.binary.rhs=rhs;
        return e;
}

EXP * makeEXP_subtraction(EXP *lhs,EXP *rhs)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=subtraction;
        e->val.binary.lhs=lhs;
        e->val.binary.rhs=rhs;
        return e;
}

EXP * makeEXP_multiplication(EXP *lhs,EXP *rhs)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=multiplication;
        e->val.binary.lhs=lhs;
        e->val.binary.rhs=rhs;
        return e;
}

EXP * makeEXP_division(EXP *lhs,EXP *rhs)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=division;
        e->val.binary.lhs=lhs;
        e->val.binary.rhs=rhs;
        return e;
}

EXP * makeEXP_equals(EXP *lhs,EXP *rhs)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=equals;
        e->val.binary.lhs=lhs;
        e->val.binary.rhs=rhs;
        return e;
}

EXP * makeEXP_notEqual(EXP *lhs,EXP *rhs)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=notEqual;
        e->val.binary.lhs=lhs;
        e->val.binary.rhs=rhs;
        return e;
}

EXP * makeEXP_greaterEqual(EXP *lhs,EXP *rhs)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=greaterEqual;
        e->val.binary.lhs=lhs;
        e->val.binary.rhs=rhs;
        return e;
}

EXP * makeEXP_lessEqual(EXP *lhs,EXP *rhs)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=lessEqual;
        e->val.binary.lhs=lhs;
        e->val.binary.rhs=rhs;
        return e;
}

EXP * makeEXP_greaterThan(EXP *lhs,EXP *rhs)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=greaterThan;
        e->val.binary.lhs=lhs;
        e->val.binary.rhs=rhs;
        return e;
}

EXP * makeEXP_lessThan(EXP *lhs,EXP *rhs)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=lessThan;
        e->val.binary.lhs=lhs;
        e->val.binary.rhs=rhs;
        return e;
}

EXP * makeEXP_and(EXP *lhs,EXP *rhs)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=expressionKindAnd;
        e->val.binary.lhs=lhs;
        e->val.binary.rhs=rhs;
        return e;
}

EXP * makeEXP_or(EXP *lhs,EXP *rhs)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=expressionKindOr;
        e->val.binary.lhs=lhs;
        e->val.binary.rhs=rhs;
        return e;
}

EXP * makeEXP_minus(EXP *exp)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=minus;
        e->val.exp=exp;
        return e;
}

EXP * makeEXP_not(EXP *exp)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=expressionKindNot;
        e->val.exp=exp;
        return e;
}

EXP * makeEXP_type(char *typeName)
{
        EXP *e=malloc(sizeof(EXP));
        e->kind=type;
        e->val.type=typeName;
        return e;
}

STMT *makeSTMT_read(EXP *identifier)
{
	STMT *s=malloc(sizeof(STMT));
	s->kind=read;
	s->val.identifier=identifier;
	return s;
}

STMT *makeSTMT_print(EXP *exp)
{
	STMT *s=malloc(sizeof(STMT));
        s->kind=print;
        s->val.exp=exp;
        return s;
}

STMT *makeSTMT_assignment(EXP *identifier, EXP *rhs)
{
        STMT *s=malloc(sizeof(STMT));
        s->kind=assignment;
        s->val.assignment.identifier=identifier;
	s->val.assignment.rhs=rhs;
        return s;
}

STMT *makeSTMT_if(EXP *condition,STMT *ifBody,STMT *elseBody)
{
        STMT *s=malloc(sizeof(STMT));
        s->kind=statementKindIf;
        s->val.ifStatement.condition=condition;
        s->val.ifStatement.ifBody=ifBody;
	s->val.ifStatement.elseBody=elseBody;
        return s;
}

STMT *makeSTMT_while(EXP *condition,STMT *body)
{
        STMT *s=malloc(sizeof(STMT));
        s->kind=statementKindWhile;
        s->val.whileLoop.condition=condition;
        s->val.whileLoop.body=body;
        return s;
}

SymbolKind getVarType(EXP *typeEXP)
{
	if(typeEXP==NULL){return k_unknown;}
	else
	{
		char *type=typeEXP->val.type;
		if(strcmp(type,"int")==0)
		{
			return k_int;
		}
		else if(strcmp(type,"float")==0)
                {
                        return k_float;
                }
		else if(strcmp(type,"string")==0)
                {
                        return k_string;
                }
		else if(strcmp(type,"bool")==0)
                {
                        return k_bool;
                }
	}
}

STMT *makeSTMT_declaration(EXP *identifier,EXP *type,EXP *rhs)
{
        STMT *s=malloc(sizeof(STMT));
        s->kind=declaration;
        s->val.declaration.identifier=identifier;
	s->val.declaration.type=getVarType(type);
        s->val.declaration.rhs=rhs;
        return s;
}

PROG *makePROG(STMT *head)
{
	PROG *p=malloc(sizeof(PROG));
	p->head=head;
	return p;
}
