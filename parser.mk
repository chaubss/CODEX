parser : main.o parser.o ptable_reader.o lexer.o token.o exceptions.o
	g++ main.o parser.o ptable_reader.o lexer.o token.o exceptions.o -o parser 

main.o : main.cpp parser.h ptable_reader.h lexer.h token.h exceptions.h
	g++ -c main.cpp

parser.o: parser.cpp parser.h
	g++ -c parser.cpp

parsing_table_reader: ptable_reader.cpp ptable_reader.h
	g++ -c ptable_reader.cpp

lexer.o : lexer.cpp lexer.h
	g++ -c lexer.cpp

token.o : token.cpp token.h
	g++ -c token.cpp

exceptions.o : exceptions.cpp exceptions.h
	g++ -c exceptions.cpp