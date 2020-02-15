#include<stdbool.h>

typedef struct EXP EXP;
typedef struct STMT STMT;
typedef struct DECL DECL;
typedef struct PROG PROG;

struct SYMBOL;

typedef enum
{
        k_int,
        k_float,
        k_string,
        k_bool,
	k_unknown
}SymbolKind;

typedef enum
{
	identifier,
	stringLiteral,
	floatLiteral,
	intLiteral,
	boolLiteral,
	addition,
	subtraction,
	multiplication,
	division,
	expressionKindAnd,
	expressionKindOr,
	equals,
	notEqual,
	greaterThan,
	lessThan,
	greaterEqual,
	lessEqual,
	minus,
	expressionKindNot,
	type
}ExpressionKind;

typedef enum
{
	read,
	print,
	statementKindIf,
	statementKindWhile,
	assignment,
	declaration
}StatementKind;


struct EXP
{
	ExpressionKind kind;
	union
	{
		char *type;//fake node that carries type info
		struct{char *identifier; struct SYMBOL *idSym; int lineno;}idE;
		char *stringLiteral;
		float floatLiteral;
		int intLiteral;
		char *boolLiteral;
		struct{EXP *lhs; EXP *rhs;} binary;
		EXP *exp;
	} val;
};

struct STMT
{
	StatementKind kind;
	union
	{
		EXP *identifier;//read()
		EXP *exp;//print()
		struct{EXP *identifier; EXP *rhs;}assignment;
		struct{EXP *condition; STMT *ifBody; STMT *elseBody;}ifStatement;
		struct{EXP *condition; STMT *body;}whileLoop;
		struct{EXP *identifier; SymbolKind type; EXP *rhs;}declaration;

	}val;
	STMT *next;
};

struct PROG
{
	STMT *head;
};

EXP *makeEXP_identifier(char *varName,int lineno);
EXP *makeEXP_boolLiteral(char *string);
EXP *makeEXP_stringLiteral(char *string);
EXP *makeEXP_intLiteral(int data);
EXP *makeEXP_floatLiteral(float data);
EXP *makeEXP_addition(EXP *lhs,EXP *rhs);
EXP *makeEXP_subtraction(EXP *lhs,EXP *rhs);
EXP *makeEXP_multiplication(EXP *lhs,EXP *rhs);
EXP *makeEXP_division(EXP *lhs,EXP *rhs);
EXP *makeEXP_equals(EXP *lhs,EXP *rhs);
EXP *makeEXP_notEqual(EXP *lhs,EXP *rhs);
EXP *makeEXP_greaterEqual(EXP *lhs,EXP *rhs);
EXP *makeEXP_lessEqual(EXP *lhs,EXP *rhs);
EXP *makeEXP_greaterThan(EXP *lhs,EXP *rhs);
EXP *makeEXP_lessThan(EXP *lhs,EXP *rhs);
EXP *makeEXP_and(EXP *lhs,EXP *rhs);
EXP *makeEXP_or(EXP *lhs,EXP *rhs);
EXP *makeEXP_minus(EXP *exp);
EXP *makeEXP_not(EXP *exp);
EXP *makeEXP_type(char *type);

STMT *makeSTMT_read(EXP *identifier);
STMT *makeSTMT_print(EXP *exp);
STMT *makeSTMT_assignment(EXP *identifier,EXP *exp);
STMT *makeSTMT_if(EXP *ifCondition,STMT *ifBody,STMT *elseBody);
STMT *makeSTMT_while(EXP *condition,STMT *body);
STMT *makeSTMT_declaration(EXP *identifier,EXP *type,EXP *rhs);

PROG *makePROG(STMT *head);
