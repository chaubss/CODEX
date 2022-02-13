lexer : main.o lexer.o token.o
	g++ main.o lexer.o token.o -o lexer 

main.o : main.cpp lexer.h token.h
	g++ -c main.cpp

lexer.o : lexer.cpp lexer.h
	g++ -c lexer.cpp

token.o : token.cpp token.h
	g++ -c token.cpp