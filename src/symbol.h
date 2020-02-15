#include"tree.h"
#define HashSize 317
typedef struct EXP EXP;
typedef struct PROG PROG;
typedef struct STMT STMT;

typedef struct SYMBOL
{
	char *name;
	SymbolKind kind;
	EXP *ptr;
	struct SYMBOL *next;
}SYMBOL;

typedef struct SymbolTable
{
	SYMBOL *table[HashSize];
	struct SymbolTable *parent;
	struct SymbolTable *child; //head of child list
	struct SymbolTable *next;
}SymbolTable;

SymbolTable *makeCactusStack(PROG *root);
void printStack(SymbolTable *t);
char *getType(SymbolKind k);
