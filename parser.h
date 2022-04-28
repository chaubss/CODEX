#ifndef PARSER
#define PARSER
#include "ptable_reader.h"
#include "semantic_object.h"
#include "token.h"
#include <iostream>
#include <vector>

class Parser {
    private:
        int temporaryTokenIndex = 0;
        int labelTokenIndex = 0;
        std::string generateTemporaryToken();
        std::string generateLabelToken();
        void modifyStack(std::vector<SemanticObject> &stack, int ruleNumber);
        ParsingTableReader *preader;
    public:
        Parser(std::vector<Token> tokens, ParsingTableReader *ptable);
};

#endif