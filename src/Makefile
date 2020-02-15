all: mini

mini: lex.yy.c y.tab.c y.tab.h main.c tree.c tree.h pretty.c pretty.h symbol.c symbol.h type.c type.h codeGen.c codeGen.h
	gcc main.c y.tab.c lex.yy.c y.tab.h tree.c pretty.c symbol.c type.c codeGen.c -o mini -lfl	
lex.yy.c: mini.l y.tab.h
	flex mini.l
y.tab.c y.tab.h: mini.y
	bison -d --yacc mini.y
clean: 
	rm lex.yy.c y.tab.c y.tab.h; rm mini
