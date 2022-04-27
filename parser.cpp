#include "ptable_reader.h"
#include "token.h"
#include "parser.h"
#include <iostream>
#include <stack>

void printStack(std::vector<std::string> &s, std::string move){
    std::cout<<"Stack: ";
    for(int i = 0; i < s.size(); i++){
        std::cout<<s[i]<<" ";
    }
    std::cout<<std::endl<<move<<std::endl;
}

std::string resolveTokenValue(Token t){
    if (t.type == "identifier") {
            return "<id>";
        } else if (t.type == "int") {
            return "<num>";
        } else if (t.type == "float") {
            return "<flt>";
        } else if (t.type == "string") {
            return "<str>";
        }
        return t.tokenString;
}

void printErrors(std::vector<std::vector<std::string>> &errorList){
    for(int i=0;i<errorList.size();i++){
        std::cout << "Error at line " << errorList[i][1] << ", token: " << errorList[i][2] << " of type: " << errorList[i][3] << " resolved to token: " << errorList[i][4] << std::endl;
    }
}

Parser::Parser(std::vector<Token> tokens, ParsingTableReader *ptable) {
// std::string tokenString, int lineNumber, std::string type, int tokenId
    tokens.push_back(Token("$", -1, "EOF", -1));
    int tokenPointer = 0;
    std::vector<std::string> stack;
    std::vector<std::vector<std::string>> errorList;
    stack.push_back("0");
    while (tokenPointer < tokens.size()) {
        Token token = tokens[tokenPointer];
        std::string tokVal = resolveTokenValue(token);
        
        auto temp = ptable->actionTable.find(make_pair(stack.back(), tokVal));
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
                std::cout << "Parsing Successful with ";
                errorList.size() == 0 ? std::cout<<"no" : std::cout<<"some";
                std::cout<<" errors."<<std::endl;
                printErrors(errorList);
                return;
            }
            if (action[0] == 's') {
                printStack(stack, action);
                stack.push_back(tokVal);
                stack.push_back(action.substr(1));
                // std::cout << "Shift " << tokVal << " state " << action.substr(1) << std::endl;
                tokenPointer++;
            } else if (action[0] == 'r') {
                int ruleNum = stoi(action.substr(1));
                printStack(stack, action);
                // std::cout << "Reduce rule " << ruleNum << std::endl;
                std::string nonTerminal = ptable->ruleConstants[ruleNum][0];
                // std::cout << "Non-Terminal: " << nonTerminal << std::endl;
                int ruleLength = stoi(ptable->ruleConstants[ruleNum][1]);
                // std::cout << "Rule length: " << ruleLength << std::endl;
                // std::cout << "Stack size: " << stack.size() << std::endl;
                for (int i = 0; i < 2 * ruleLength; i++) {
                    stack.pop_back();
                }
                std::string lastState = stack.back();
                // std::cout << "Last state: " << lastState << std::endl;
                stack.push_back(nonTerminal);
                std::string toPush = ptable->gotoTable[make_pair(lastState, nonTerminal)];
                printStack(stack, "goto " + toPush);
                stack.push_back(toPush);
                // std::cout << "Pushing " << toPush << std::endl;
            }
        } else {

            // handle error
            std::cout << "Error." << std::endl;
            std::cout << "Token: " << token.tokenString << std::endl;
            std::cout << "Line: " << token.lineNumber << std::endl;
            std::cout << "Token Type: " << token.type << " " << tokVal << std::endl;
            std::cout << "State: " << stack.back() << std::endl;
            errorList.push_back({stack.back(), std::to_string(token.lineNumber), token.tokenString, token.type, tokVal});
            std::vector<std::string> safeSymbols = {";", "}", "$"};
            int safeSymbolFound = 0;
            std::cout<<"PANIC MODE!\n";
            for(int i = 0; i < safeSymbols.size(); i++) {
                if(tokVal == safeSymbols[i]){
                    tokenPointer++;
                    break;
                }
            }
            while(tokenPointer < tokens.size()) {
                Token tempToken = tokens[tokenPointer];
                std::string tempTokVal = resolveTokenValue(tempToken);
                for(int i = 0; i < safeSymbols.size(); i++){
                    if(tempTokVal == safeSymbols[i]){
                        tokenPointer++;
                        safeSymbolFound = 1;
                        break;
                    }
                }
                if(safeSymbolFound == 1)
                    break;
                tokenPointer++;                
            }
            // stack.pop_back();
            // stack.pop_back();

            // return;
        }
        
    }

}
