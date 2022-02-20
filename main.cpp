#include "lexer.h"
#include "exceptions.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: ./lexer <input file>" << std::endl;
        return 1;
    }
    std::string fileName = argv[1];
    try {
        Lexer lex = Lexer(fileName);
        while (true) {
            Token *token = lex.getNextToken();
            if (token == NULL) {
                break;
            }
            std::cout << token->lineNumber << "\t" << token->tokenString << "\t" << token->type << std::endl;
        }
    } catch (FileNotFoundException e) {
        std::cout << "File not found: " << e.getFileName() << std::endl;
    } catch (LexicalException e) {
        std::cout << "Lexical error on line " << e.getLineNumber() << ": " << e.getMessage() << std::endl;
    }
    return 0;
}
