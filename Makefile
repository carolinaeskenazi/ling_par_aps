all:
	bison -d cafelang.y
	flex cafelang.l
	gcc -o cafelang main.c cafelang.tab.c lex.yy.c