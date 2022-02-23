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
            Token *token = lex.getNextToken();   //fetch stored tokens from vector tokens
            if (token == NULL) {       // NULL will be returned if request exceeded the stored tokens
                break;                 // to break the while loop
            }
            std::cout << token->lineNumber << "\t" << token->tokenString << "\t" << token->type << std::endl;
        }
    } catch (FileNotFoundException e) {
        std::cout << "\033[1;31mFileNotFoundException\033[0m  ";
        std::cout << "File not found: " << e.getFileName() << std::endl;
    } catch (LexicalException e) {
        std::cout << "\033[1;31mLexicalException\033[0m  ";
        std::cout << "Lexical error on line " << e.getLineNumber() << std::endl << std::endl;
        std::cout << "\033[1;32m"  << e.getLineNumber() << " \033[0m" << e.getLine() << std::endl;
        std::cout << "\033[1;36mMessage: \033[0m" << e.getMessage() << std::endl;
    }
    return 0;
}
