output : erplag.o codegen.o ast.o typeChecker.o lexTest.o lexer.o parser.o lexer.h typeChecker.h lexerDef.h symbolTable.o parser.h parserDef.h symbolTable.h codegen.h
	gcc -o erplag.exe erplag.o codegen.o ast.o lexTest.o lexer.o parser.o symbolTable.o typeChecker.o
	./erplag.exe $(FILE).erp
	nasm -felf64 code.asm
	gcc -no-pie code.o -o $(FILE).exe
	rm code.o

erplag : erplag.o codegen.o ast.o typeChecker.o lexTest.o lexer.o parser.o lexer.h typeChecker.h lexerDef.h symbolTable.o parser.h parserDef.h symbolTable.h codegen.h
	gcc -o erplag.exe erplag.o codegen.o ast.o lexTest.o lexer.o parser.o symbolTable.o typeChecker.o
	make objClean

allExec : erplag.o codegen.o astDriver.o ast.o typeChecker.o lexTest.o lexer.o parser.o symbolTableDriver.o lexer.h typeChecker.h lexerDef.h symbolTable.o parser.h parserDef.h symbolTable.h codegen.h
	gcc -o ast.exe astDriver.o ast.o lexTest.o lexer.o parser.o
	gcc -o ST.exe symbolTableDriver.o ast.o lexTest.o lexer.o parser.o symbolTable.o typeChecker.o
	gcc -o erplag.exe erplag.o codegen.o ast.o lexTest.o lexer.o parser.o symbolTable.o typeChecker.o

erplag.o : erplag.c
	gcc -c erplag.c

codegen.o : codegen.c
	gcc -c codegen.c

astDriver.o : astDriver.c
	gcc -c astDriver.c

ast.o : ast.c
	gcc -c ast.c

typeChecker.o : typeChecker.c
	gcc -c typeChecker.c

parser.o : parser.c
	gcc -c parser.c

lexTest.o : lexTest.c
	gcc -c lexTest.c

lexer.o : lexer.c
	gcc -c lexer.c

symbolTableDriver.o : symbolTableDriver.c
	gcc -c symbolTableDriver.c

asm :
	make -f make.asm

clean :
	rm *.o
	rm *.exe

objClean :
	rm *.o