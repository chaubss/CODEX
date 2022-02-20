g++ -c exceptions.cpp
g++ -c token.cpp
g++ -c lexer.cpp
g++ -c main.cpp
g++ main.o lexer.o token.o exceptions.o -o lexer 

