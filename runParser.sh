g++ -c exceptions.cpp
g++ -c token.cpp
g++ -c lexer.cpp
g++ -c ptable_reader.cpp
g++ -c semantic_object.cpp
g++ -c parser.cpp
g++ -c main.cpp
g++ main.o parser.o semantic_object.o ptable_reader.o lexer.o token.o exceptions.o -o parser