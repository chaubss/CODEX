#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <unordered_set>

class Lexer {

    std::string inputFile;
    std::unordered_set<std::string> reservedKeywords;

    void initializeReservedKeywords();
    std::string findWord(std::string input, int *linePointer);
    void addToken(std::string token, int line, std::string type);

    public:
        Lexer(std::string inputFile);
        std::string getNextToken();
};

#endif
