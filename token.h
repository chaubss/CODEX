#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

class Token {

    public:
        std::string tokenString;
        std::string type;
        int lineNumber;
        int tokenId;
        Token(std::string tokenString, int lineNumber, std::string type, int tokenId);
};

#endif
