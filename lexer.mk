lexer : main_lexer.o lexer.o token.o exceptions.o
	g++ main_lexer.o lexer.o token.o exceptions.o -o lexer -std=c++14

main_lexer.o : main_lexer.cpp parser.h ptable_reader.h lexer.h token.h exceptions.h
	g++ -c main_lexer.cpp -std=c++14

lexer.o : lexer.cpp lexer.h
	g++ -c lexer.cpp -std=c++14

token.o : token.cpp token.h
	g++ -c token.cpp -std=c++14

exceptions.o : exceptions.cpp exceptions.h
	g++ -c exceptions.cpp -std=c++14