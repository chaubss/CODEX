#include "lexer.h"
#include <iostream>
#include <string>

int main() {
    Lexer lex = Lexer("test.cdx");
    while (true) {
        Token *token = lex.getNextToken();
        if (token == NULL) {
            break;
        }
        std::cout << token->lineNumber << "\t" << token->tokenString << "\t" << token->type << std::endl;
    }
    return 0;
}
