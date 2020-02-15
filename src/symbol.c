#include<stdio.h>
#include<stdlib.h>
#include"string.h"
#include"symbol.h"

SymbolTable *initSymbolTable()
{
	SymbolTable *t=malloc(sizeof(SymbolTable));
	for(int i=0;i<HashSize;i++)
	{
		t->table[i]=NULL;
	}

	t->parent=NULL;
	return t;
}

SymbolTable *scopeSymbolTable(SymbolTable *s)
{
	SymbolTable *t=initSymbolTable();
	t->parent=s;
	return t;
}

SymbolTable *unscopeSymbolTable(SymbolTable *t)
{
	return t->parent;
}

int Hash(char *str)
{
	unsigned int hash=0;
	while(*str) hash=(hash << 1)+ *str++;
	return hash % HashSize;
}

SYMBOL *putSymbol(SymbolTable *t,char *name,SymbolKind kind)
{
	int i=Hash(name);
	for (SYMBOL *s = t->table[i]; s; s = s->next)
	{
		if (strcmp(s->name, name) == 0);
		{
			printf("\n%s%s%s%s%s\n","Error: ","\"",name,"\""," is already declared");
                        exit(1);
		}
	}
	SYMBOL *s = malloc(sizeof(SYMBOL));
	s->name = name;
	s->kind = kind;
	s->next = t->table[i];
	t->table[i] = s;
	return s;
}

SYMBOL *getSymbol(SymbolTable *t, char *name) {
	int i = Hash(name);
	// Check the current scope
	for (SYMBOL *s = t->table[i]; s; s = s->next) {
		if (strcmp(s->name, name) == 0) return s;
	}
	// Check for existence of a parent scope
	if (t->parent == NULL)
		return NULL;
	// Check the parent scopes
	return getSymbol(t->parent, name);
}

void makeCactusStack3(EXP *e,SymbolTable *currentScope)
{
	switch(e->kind)
	{
		case identifier:;
			char *name=e->val.idE.identifier;
			//printf("\n%s%s\n","Identifier Name: ",name);
			if(getSymbol(currentScope,name)==NULL)
			{
				printf("\n%s%s%s%s%s\n","Error: ","\"",name,"\""," is not declared");
				exit(1);
			}
			else
			{//之前的问题是，declaration情况以外出现的identifier没有对应的idSym
				e->val.idE.idSym=getSymbol(currentScope,name); //所有identifier,全部连接到最近一次declaration时(current scope)所生成的symbol
			}
			break;
		case stringLiteral:
		case intLiteral:
		case floatLiteral:
			break;
		case addition:
		case subtraction:
		case multiplication:
		case division:
		case expressionKindAnd:
		case expressionKindOr:
		case equals:
		case notEqual:
		case greaterEqual:
		case lessEqual:
		case greaterThan:   //如果有case没覆盖到，会导致该种exp中的identifier没有指向对应的SYMBOL
		case lessThan:
			makeCactusStack3(e->val.binary.lhs,currentScope);
			makeCactusStack3(e->val.binary.rhs,currentScope);
			break;
		case minus:
		case expressionKindNot:
		       makeCactusStack3(e->val.exp,currentScope);
		       break;	       
	}
}

void makeCactusStack2(STMT *s,SymbolTable *parentScope)
{

        if(s==NULL){return;}
        makeCactusStack2(s->next,parentScope);
	switch(s->kind)
	{
		case read:
			makeCactusStack3(s->val.identifier,parentScope);
			break;
		case print:
			makeCactusStack3(s->val.exp,parentScope);
			break;
		case assignment:
			makeCactusStack3(s->val.assignment.identifier,parentScope);
			makeCactusStack3(s->val.assignment.rhs,parentScope);
			break;
		case statementKindIf:
			{
				makeCactusStack3(s->val.ifStatement.condition,parentScope); 
				SymbolTable *childScope=initSymbolTable(); //make a child scope
				childScope->parent=parentScope;
				if(parentScope->child==NULL){parentScope->child=childScope;} //add child scope to parent scope's child list
				else {parentScope->child->next=childScope;}
				makeCactusStack2(s->val.ifStatement.ifBody,childScope);
				if(s->val.ifStatement.elseBody!=NULL) //make another child
				{
					SymbolTable *childScope2=initSymbolTable();
	                     		childScope2->parent=parentScope;
                	        	parentScope->child->next=childScope2; //parent scope already have a child scope of if's body
                        		makeCactusStack2(s->val.ifStatement.elseBody,childScope2);
				}
				break;
			}
		case statementKindWhile:
			{
				makeCactusStack3(s->val.whileLoop.condition,parentScope);
				SymbolTable *childScope=initSymbolTable(); //make a child scope
                        	childScope->parent=parentScope;
                        	if(parentScope->child==NULL){parentScope->child=childScope;} //add child scope to parent scope's child list
                        	else {parentScope->child->next=childScope;}
                        	makeCactusStack2(s->val.whileLoop.body,childScope);
				break;
			}

		case declaration:
			s->val.declaration.identifier->val.idE.idSym=putSymbol(parentScope,s->val.declaration.identifier->val.idE.identifier,s->val.declaration.type); //put the identifier's info in to a block of the hashtable, and the EXP retain a pointer to that block
                        makeCactusStack3(s->val.declaration.rhs,parentScope);
                        break;
	}
}

SymbolTable *makeCactusStack(PROG *root)
{

	if(root==NULL){return NULL;}
	SymbolTable *classScope=initSymbolTable();
	makeCactusStack2(root->head,classScope);
	//if(classScope->child==NULL){printf("\n%s","table error");}
	return classScope;
}

char *getType(SymbolKind k)
{
	switch(k)
	{
		case k_int:
			return "int";
		case k_float:
			return "float";
		case k_string:
			return "string";
		case k_bool:
			return "bool";
		case k_unknown:
			return "unknown";
	}
}

void printStack(SymbolTable *t)
{
	for(int i=0;i<317;i++)
	{
		for(SYMBOL *s=t->table[i];s;s=s->next)
		{
			printf("\t%s\t%s\n",s->name,getType(s->kind));
		}
	}
	for(SymbolTable *c=t->child;c;c=c->next)
	{
		printf("%s","\n");
		printStack(c);
	}
}
