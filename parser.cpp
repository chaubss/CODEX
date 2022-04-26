#include "ptable_reader.h"
#include "token.h"
#include "parser.h"
#include <iostream>
#include <stack>

Parser::Parser(std::vector<Token> tokens, ParsingTableReader *ptable) {
// std::string tokenString, int lineNumber, std::string type, int tokenId
    tokens.push_back(Token("$", -1, "EOF", -1));
    int tokenPointer = 0;
    std::stack<std::string> stack;
    stack.push("0");
    while (tokenPointer < tokens.size()) {
        Token token = tokens[tokenPointer];
        std::string tokVal = token.tokenString;
        if (token.type == "identifier" || token.type == "int" || token.type == "float" || token.type == "string") {
            tokVal = "<id>";
        }
        auto temp = ptable->actionTable.find(make_pair(stack.top(), tokVal));
        if (temp != ptable->actionTable.end()) {
            std::string action = temp->second;
            // std::cout << "Action: " << action << std::endl;
            // if (action == "") {
            //     std::cout << "Error." << std::endl;
            //     std::cout << "Token: " << tokVal << std::endl;
            //     return;
            //     // TODO: error handling
            // }
            if (action == "acc") {
                std::cout << "Accepted." << std::endl;
                return;
            }
            if (action[0] == 's') {
                stack.push(tokVal);
                stack.push(action.substr(1));
                // std::cout << "Shift " << tokVal << " state " << action.substr(1) << std::endl;
                tokenPointer++;
            } else if (action[0] == 'r') {
                int ruleNum = stoi(action.substr(1));
                // std::cout << "Reduce rule " << ruleNum << std::endl;
                std::string nonTerminal = ptable->ruleConstants[ruleNum][0];
                // std::cout << "Non-Terminal: " << nonTerminal << std::endl;
                int ruleLength = stoi(ptable->ruleConstants[ruleNum][1]);
                // std::cout << "Rule length: " << ruleLength << std::endl;
                // std::cout << "Stack size: " << stack.size() << std::endl;
                for (int i = 0; i < 2 * ruleLength; i++) {
                    stack.pop();
                }
                std::string lastState = stack.top();
                // std::cout << "Last state: " << lastState << std::endl;
                stack.push(nonTerminal);
                std::string toPush = ptable->gotoTable[make_pair(lastState, nonTerminal)];
                stack.push(toPush);
                // std::cout << "Pushing " << toPush << std::endl;
            }
        } else {
            std::cout << "Error." << std::endl;
            std::cout << "Token: " << token.tokenString << std::endl;
            std::cout << "Token Type: " << token.type << std::endl;
            std::cout << "State: " << stack.top() << std::endl;
            return;
        }
        
    }

}
