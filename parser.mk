parser : main.o parser.o ptable_reader.o lexer.o token.o exceptions.o
	g++ main.o parser.o ptable_reader.o lexer.o token.o exceptions.o -o parser -std=c++14

main.o : main.cpp parser.h ptable_reader.h lexer.h token.h exceptions.h
	g++ -c main.cpp -std=c++14

parser.o: parser.cpp parser.h
	g++ -c parser.cpp -std=c++14

parsing_table_reader: ptable_reader.cpp ptable_reader.h
	g++ -c ptable_reader.cpp -std=c++14

lexer.o : lexer.cpp lexer.h
	g++ -c lexer.cpp -std=c++14

token.o : token.cpp token.h
	g++ -c token.cpp -std=c++14

exceptions.o : exceptions.cpp exceptions.h
	g++ -c exceptions.cpp -std=c++14