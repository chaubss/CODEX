#include "ptable_reader.h"
#include "token.h"
#include "parser.h"
#include "semantic_object.h"
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <set>

std::string Parser::generateTemporaryToken() {
    return "t" + std::to_string(temporaryTokenIndex++);
}

std::string Parser::generateLabelToken() {
    return "l" + std::to_string(labelTokenIndex++);
}

void  Parser::modifyStack(std::vector<SemanticObject> &stack, int ruleNumber) {
    SemanticObject so;
    bool toPush = true;
    switch (ruleNumber) {
        case 0:
        std::cout << "asdf" << std::endl;
        toPush = false;
        break;
        case 1: {
            SemanticObject stmts = stack.back();
            stack.pop_back();
            SemanticObject stmt = stack.back();
            stack.pop_back();
            
            so.code = stmt.code + "\n" + stmts.code;
            break;
        }
        case 2:
        toPush = false;
        break;
        case 4:
        toPush = false;
        break;
        case 8:
        toPush = false;
        break;
        case 23: {
            SemanticObject _ = stack.back();
            stack.pop_back();
            SemanticObject stmts = stack.back();
            stack.pop_back();
            SemanticObject __ = stack.back();
            stack.pop_back();
            SemanticObject ___ = stack.back();
            stack.pop_back();
            SemanticObject expr = stack.back();
            stack.pop_back();
            SemanticObject ____ = stack.back();
            stack.pop_back();
            SemanticObject _____ = stack.back();
            stack.pop_back();
            so.temp = "";
            std::string ifL = generateLabelToken();
            std::string skipL = generateLabelToken();
            so.code = expr.code + "\nif (" + expr.temp + ") goto " + ifL + "\ngoto " + skipL + "\n" + ifL + ":\n" + stmts.code + "\n" + skipL + ":\n";
            break;
        }
        case 27: {
            SemanticObject expr = stack.back();
            stack.pop_back();
            SemanticObject _ = stack.back();
            stack.pop_back();
            SemanticObject id = stack.back();
            stack.pop_back();
            so.temp = "";
            so.code = expr.code + "\n" + id.temp + " := " + expr.temp;
            std::cout << "******************" << std::endl;
            std::cout << so.code << std::endl;
            std::cout << "******************" << std::endl;
            break;
        }
        case 28: {
            so.temp = generateTemporaryToken();
            SemanticObject op2 = stack.back();
            stack.pop_back();
            SemanticObject op = stack.back();
            stack.pop_back();
            SemanticObject op1 = stack.back();
            stack.pop_back();
            so.code = op1.code + "\n" + op2.code + "\n";
            so.code += so.temp + " := " + op1.temp + " " + op.temp + " " + op2.temp;
            break;
        }
        case 29: {
            so.temp = generateTemporaryToken();
            SemanticObject op2 = stack.back();
            stack.pop_back();
            SemanticObject op = stack.back();
            stack.pop_back();
            SemanticObject op1 = stack.back();
            stack.pop_back();
            so.code = op1.code + "\n" + op2.code + "\n";
            so.code += so.temp + " := " + op1.temp + " " + op.temp + " " + op2.temp;
            break;
        }
         case 30: {
            so.temp = generateTemporaryToken();
            SemanticObject op2 = stack.back();
            stack.pop_back();
            SemanticObject op = stack.back();
            stack.pop_back();
            SemanticObject op1 = stack.back();
            stack.pop_back();
            so.code = op1.code + "\n" + op2.code + "\n";
            so.code += so.temp + " := " + op1.temp + " " + op.temp + " " + op2.temp;
            break;
        }
         case 31: {
            so.temp = generateTemporaryToken();
            SemanticObject op2 = stack.back();
            stack.pop_back();
            SemanticObject op = stack.back();
            stack.pop_back();
            SemanticObject op1 = stack.back();
            stack.pop_back();
            so.code = op1.code + "\n" + op2.code + "\n";
            so.code += so.temp + " := " + op1.temp + " " + op.temp + " " + op2.temp;
            break;
        }
         case 32: {
            so.temp = generateTemporaryToken();
            SemanticObject op2 = stack.back();
            stack.pop_back();
            SemanticObject op = stack.back();
            stack.pop_back();
            SemanticObject op1 = stack.back();
            stack.pop_back();
            so.code = op1.code + "\n" + op2.code + "\n";
            so.code += so.temp + " := " + op1.temp + " " + op.temp + " " + op2.temp;
            break;
        }
         case 33: {
            so.temp = generateTemporaryToken();
            SemanticObject op2 = stack.back();
            stack.pop_back();
            SemanticObject op = stack.back();
            stack.pop_back();
            SemanticObject op1 = stack.back();
            stack.pop_back();
            so.code = op1.code + "\n" + op2.code + "\n";
            so.code += so.temp + " := " + op1.temp + " " + op.temp + " " + op2.temp;
            break;
        }
        case 34:
        toPush = false;
        break;
        case 35: {
            so.temp = generateTemporaryToken();
            SemanticObject op2 = stack.back();
            stack.pop_back();
            SemanticObject op = stack.back();
            stack.pop_back();
            SemanticObject op1 = stack.back();
            stack.pop_back();
            so.code = op1.code + "\n" + op2.code + "\n";
            so.code += so.temp + " := " + op1.temp + " " + op.temp + " " + op2.temp;
            std::cout << "-----------------------------------------" << std::endl;
            std::cout << so.code << std::endl;
            std::cout << "-----------------------------------------" << std::endl;
            break;
        }
        case 36: {
            so.temp = generateTemporaryToken();
            SemanticObject op2 = stack.back();
            stack.pop_back();
            SemanticObject op = stack.back();
            stack.pop_back();
            SemanticObject op1 = stack.back();
            stack.pop_back();
            so.code = op1.code + "\n" + op2.code + "\n";
            so.code += so.temp + " := " + op1.temp + " " + op.temp + " " + op2.temp;
            break;
        }
        case 37:
        toPush = false;
        break;
        case 38: {
            so.temp = generateTemporaryToken();
            SemanticObject op2 = stack.back();
            stack.pop_back();
            SemanticObject op = stack.back();
            stack.pop_back();
            SemanticObject op1 = stack.back();
            stack.pop_back();
            so.code = op1.code + "\n" + op2.code + "\n";
            so.code += so.temp + " := " + op1.temp + " " + op.temp + " " + op2.temp;
            break;
        }
        case 39: {
            so.temp = generateTemporaryToken();
            SemanticObject op2 = stack.back();
            stack.pop_back();
            SemanticObject op = stack.back();
            stack.pop_back();
            SemanticObject op1 = stack.back();
            stack.pop_back();
            so.code = op1.code + "\n" + op2.code + "\n";
            so.code += so.temp + " := " + op1.temp + " " + op.temp + " " + op2.temp;
            break;
        }
        case 40:
        toPush = false;
        break;
        case 41: {
            SemanticObject _ = stack.back();
            stack.pop_back();
            SemanticObject expr = stack.back();
            stack.pop_back();
            SemanticObject __ = stack.back();
            stack.pop_back();
            so.code = expr.code;
            so.temp = expr.temp;
            break;
        }
        case 42:
        toPush = false;
        break;
        case 43:
        toPush = false;
        break;
        case 44:
        toPush = false;
        break;
        case 45:
        toPush = false;
        break;
        case 58: {
            so.temp = stack.back().temp;
            so.code = "";
            stack.pop_back();
            break;
        }
        case 59: {
            so.temp = generateTemporaryToken();
            so.code = so.temp + " := " + stack.back().temp;
            stack.pop_back();
            break;
        }
        case 60: {
            so.temp = generateTemporaryToken();
            so.code = so.temp + " := " + stack.back().temp;
            stack.pop_back();
            break;
        }
        case 61: {
            so.temp = generateTemporaryToken();
            so.code = so.temp + " := -" + stack.back().temp;
            stack.pop_back();
            break;
        }
        case 62: {
            so.temp = generateTemporaryToken();
            so.code = so.temp + " := " + stack.back().temp;
            stack.pop_back();
            break;
        }
        case 63: {
            so.temp = generateTemporaryToken();
            so.code = so.temp + " := " + stack.back().temp;
            stack.pop_back();
            break;
        }
        case 64: {
            so.temp = generateTemporaryToken();
            so.code = so.temp + " := " + stack.back().temp;
            stack.pop_back();
            break;
        }
        case 65: {
            so.temp = generateTemporaryToken();
            so.code = so.temp + " := -" + stack.back().temp;
            stack.pop_back();
            break;
        }
        default: {
            so.temp = "";
            so.code = "";
            int toRemove = stoi(preader->ruleConstants[ruleNumber][1]);
            for (int i = 0; i < toRemove; i++) {
                stack.pop_back();
            }
        }
    }
    // if (so.code != "" && so.temp != "") {
    //     stack.push_back(so);
    //     std::cout << "Pushing " << stack.back().code << std::endl;
    // }
    if (toPush) {
        stack.push_back(so);
        std::cout << "Pushing " << ((stack.back().code == "") ? "<empty>" : stack.back().code) << " " << ((stack.back().temp == "") ? "<empty>" : stack.back().temp) << std::endl;
    }
}

void printStack(std::vector<std::string> &s, std::string move){
    // std::cout<<"Stack: ";
    // for(int i = 0; i < s.size(); i++){
    //     std::cout<<s[i]<<" ";
    // }
    // std::cout<<std::endl<<move<<std::endl;
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

void printErrors(std::vector<std::vector<std::string> > &errorList){
    for(int i=0;i<errorList.size();i++){
        std::cout << "Error at line " << errorList[i][1] << ", token: " << errorList[i][2] << " of type: " << errorList[i][3] << " resolved to token: " << errorList[i][4] << std::endl;
    }
}

/*
27 ASSIGN -> ID = EXPR { ID.place = EXPR.place }
//////////////////////////////////////////////////////////////////////////////////
28 EXPR -> EXPR == TERM { ti = genTemp(); ti = EXPR.place == TERM.place }
29 EXPR -> EXPR != TERM { ti = genTemp(); ti = EXPR.place != TERM.place }
30 EXPR -> EXPR > TERM { ti = genTemp(); ti = EXPR.place > TERM.place }
31 EXPR -> EXPR < TERM { ti = genTemp(); ti = EXPR.place < TERM.place }
32 EXPR -> EXPR >= TERM { ti = genTemp(); ti = EXPR.place >= TERM.place }
33 EXPR -> EXPR <= TERM { ti = genTemp(); ti = EXPR.place <= TERM.place }
///////////////////////////////////////////////////////////////////////////////////
34 EXPR -> TERM { EXPR.place = TERM.place }
///////////////////////////////////////////////////////////////////////////////////
35 TERM -> TERM + TERM2 { ti = genTemp(); ti = TERM.place + TERM2.place; }
36 TERM -> TERM - TERM2 { ti = genTemp(); ti = TERM.place - TERM2.place; }
////////////////////////////////////////////////////////////////////////////////////
37 TERM -> TERM2 { TERM.place = TERM2.place }
////////////////////////////////////////////////////////////////////////////////////
38 TERM2 -> TERM2 * TERM3 { ti = genTemp(); ti = TERM2.place * TERM3.place; }
39 TERM2 -> TERM2 / TERM3 { ti = genTemp(); ti = TERM2.place / TERM3.place; }
////////////////////////////////////////////////////////////////////////////////////
40 TERM2 -> TERM3 { TERM2.place = TERM3.place }
41 TERM3 -> ( EXPR ) { TERM3.place = EXPR.place }
42 TERM3 -> ID { TERM3.place = ID.place }
43 TERM3 -> NUM { TERM3.place = NUM.place }
44 TERM3 -> STR { TERM3.place = STR.place }
45 TERM3 -> FLT { TERM.place = FLT.place }
////////////////////////////////////////////////////////////////////////////////////
58 ID -> <id> { ID.place = tokenString; }
NUM -> <num>
NUM -> + <num>
NUM -> - <num>
STR -> <str>
FLT -> <flt>
FLT -> + <flt>
FLT -> - <flt>
*/


Parser::Parser(std::vector<Token> tokens, ParsingTableReader *ptable) {
// std::string tokenString, int lineNumber, std::string type, int tokenId
    preader = ptable;
    tokens.push_back(Token("$", -1, "EOF", -1));
    int tokenPointer = 0;
    std::vector<std::string> stack;
    std::vector<std::string> expressionStack;
    std::vector<SemanticObject> semanticStack;

    std::vector<std::vector<std::string> > errorList;
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
                std::cout << semanticStack.back().code << std::endl;
                std::cout << semanticStack.size() << std::endl;
                return;
            }
            if (action[0] == 's') {
                printStack(stack, action);
                stack.push_back(tokVal);
                stack.push_back(action.substr(1));
                if (token.type == "operator" || token.type == "identifier" || token.type == "operator/sign" || token.type == "int" || token.type == "float" || token.type == "string") {
                    expressionStack.push_back(token.tokenString);
                }
                // push into semantic stack
                SemanticObject sobj;
                sobj.code = "";
                sobj.temp = token.tokenString;
                semanticStack.push_back(sobj);
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
                std::set<int> operationRules {38, 39, 35, 36, 28, 29, 30, 31, 32, 33};
                if (operationRules.count(ruleNum)) {
                    std::string secondOperand = expressionStack.back();
                    expressionStack.pop_back();
                    std::string operation = expressionStack.back();
                    expressionStack.pop_back();
                    std::string firstOperand = expressionStack.back();
                    expressionStack.pop_back();
                    std::string temp = generateTemporaryToken();
                    expressionStack.push_back(temp);
                    std::string threeCodeRule = temp + " = " + firstOperand + " " + operation + " " + secondOperand + ";";
                    // std::cout << threeCodeRule << std::endl;
                }
                std::cout << "Calling with rule number: " << ruleNum << std::endl;
                modifyStack(semanticStack, ruleNum);
                // semantic conditions
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
            std::vector<std::string> errorListItem{ stack.back(), std::to_string(token.lineNumber), token.tokenString, token.type, tokVal };
            errorList.push_back(errorListItem);
            std::vector<std::string> safeSymbols {";", "}", "$"};
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
