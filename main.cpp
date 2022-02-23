#include "lexer.h"
#include "exceptions.h"
#include <iostream>
#include <string>
#include <iomanip>

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
            std::cout << std::left << "Token " << std::setw(7) << token->tokenId << "Line " << std::setw(6) << token->lineNumber << std::setw(15) << token->type << token->tokenString << std::endl << std::right;
        }
    } catch (FileNotFoundException e) {
        std::cout << "\033[1;31mFileNotFoundException\033[0m  ";
        std::cout << "File not found: " << e.getFileName() << std::endl;
    } catch (LexicalException e) {
        std::cout << "\033[1;31mLexicalException\033[0m  ";
        std::cout << "Lexical error on line " << e.getLineNumber() << std::endl << std::endl;
        std::cout << "\033[1;32m"  << e.getLineNumber() << " \033[0m" << e.getLine();
        std::cout << "  ";
        int lineNumber = e.getLineNumber();
        while (lineNumber > 9) {
            lineNumber /= 10;
            std::cout << " ";
        }
        for (int i = 0; i < e.getLinePointer(); i++) {
            std::cout << " ";
        }
        std::cout << "\033[1;31m^\033[0m" << std::endl;
        std::cout << "\033[1;36mMessage: \033[0m" << e.getMessage() << std::endl;

    }
    return 0;
}
