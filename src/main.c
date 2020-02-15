#include<stdio.h>
#include<string.h>
#include"codeGen.h"
PROG *root;
char *mode="";
int yylex();
void yyparse();
int main(int argc, char **argv)
{
	if(strcmp(argv[1],"tokens")==0)
	{
		mode="tokens";
		while(yylex()){};
	}
	else if(strcmp(argv[1],"scan")==0)
        {
                while(yylex()){};
                printf("OK\n");
        }
	else if(strcmp(argv[1],"parse")==0)
	{
		yyparse();
		printf("OK\n");
	}
	else if(strcmp(argv[1],"pretty")==0)
        {
		yyparse();
                prettyPROG(root);
        }
	 else if(strcmp(argv[1],"symbol")==0)
        {
                yyparse();
                SymbolTable *t=makeCactusStack(root);
		printf("%s","\n");
		printStack(t);
        }
	 else if(strcmp(argv[1],"type")==0)
        {
                yyparse();
                SymbolTable *t=makeCactusStack(root);
		printf("%s","\n");
                printStack(t);
		checkPROG(root);
		printf("\nOK\n");
        }
	 else if(strcmp(argv[1],"codegen")==0)
        {
                yyparse();
                SymbolTable *t=makeCactusStack(root);
                printf("%s","\n");
                printStack(t);
                checkPROG(root);
		int length=strlen(argv[2]);
		int position=0;
		for(int i=0;i<length;i++)
		{
			if(argv[2][i]=='.'){position=i;break;}
		}
		char filename[position+2];
		for(int j=0;j<position+1;j++)
		{
			filename[j]=argv[2][j];
		}
		filename[position+1]='c';
		filename[position+2]='\0';
		genPROG(root,filename);
                printf("\nOK\n");
        }



	return 0;
}
