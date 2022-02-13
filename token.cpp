#include "token.h"
#include <iostream>

Token::Token(std::string tokenString, int lineNumber, std::string type, int tokenId) {
    this->tokenString = tokenString;
    this->lineNumber = lineNumber;
    this->tokenId = tokenId;
    this->type = type;
}