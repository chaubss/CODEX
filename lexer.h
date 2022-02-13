#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <iostream>
#include <unordered_set>
#include <vector>

class Lexer {

    std::string inputFile;
    std::unordered_set<std::string> reservedKeywords;
    std::vector<Token> tokens;
    int tokenPointer;
    void initializeReservedKeywords();
    std::string findWord(std::string input, int *linePointer);
    void addToken(std::string token, int line, std::string type);

    public:
        Lexer(std::string inputFile);
        Token* getNextToken();
};

#endif
