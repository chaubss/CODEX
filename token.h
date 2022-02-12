#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

class Token {
    std::string tokenString;
    int lineNumber;
    int tokenId;

    public:
        Token(std::string tokenString, int lineNumber, int tokenId);
};

#endif
