#include<stdio.h>
#include "type.h"

void genPROG(PROG *root,char *filename);
void genSTMT(STMT *s,FILE *fp);
void genEXP(EXP *e,FILE *fp);
