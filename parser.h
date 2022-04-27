#ifndef PARSER
#define PARSER
#include "ptable_reader.h"
#include "token.h"
#include <iostream>
#include <vector>

class Parser {
    public:
    Parser(std::vector<Token> tokens, ParsingTableReader *ptable);
};

#endif