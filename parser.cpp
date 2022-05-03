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
        case 2: {
            so.code = "";
            so.temp = "";
            break;
        }
        case 4:
        toPush = false;
        break;
        case 6:
        toPush = false;
        break;
        case 8: {
            stack.pop_back();
            SemanticObject ass = stack.back();
            stack.pop_back();
            so.code = ass.code;
            so.temp = ass.temp;
            break;
        }
        case 9:
        {
            stack.pop_back();
            SemanticObject defn = stack.back();
            stack.pop_back();
            so.code = defn.code;
            so.temp = defn.temp;
            break;
        }
        case 10:
        {
            stack.pop_back();
            SemanticObject fcall = stack.back();
            stack.pop_back();
            so.code = fcall.code;
            so.temp = fcall.temp;
            break;
        }
        case 11: {
            SemanticObject defnList = stack.back();
            stack.pop_back(); stack.pop_back();
            so.temp = "";
            so.code = defnList.code;
            break;
        }
        case 12: {
            SemanticObject defnList = stack.back();
            stack.pop_back(); stack.pop_back();
            SemanticObject imi = stack.back();
            stack.pop_back();
            so.temp = "";
            so.code = imi.code + "\n" + defnList.code;
            break;
        }
        case 13: {
            SemanticObject imi = stack.back();
            stack.pop_back();
            so.code = imi.code;
            so.temp = imi.temp;
            break;
        }
        case 14: {
            SemanticObject id = stack.back();
            stack.pop_back();
            so.code = id.code;
            so.temp = id.temp;
            break;
        }
        case 15: {
            SemanticObject expr = stack.back();
            stack.pop_back(); stack.pop_back();
            SemanticObject id = stack.back();
            stack.pop_back();
            so.code = expr.code + "\n" + id.temp + " := " + expr.temp;
            break;
        }
        case 16: {
            stack.pop_back();
            so.code = stack.back().code;
            stack.pop_back(); stack.pop_back(); stack.pop_back(); stack.pop_back(); stack.pop_back(); stack.pop_back(); stack.pop_back();
            break;
        }
        case 21: {
            stack.pop_back();
            SemanticObject stmt2 = stack.back();
            stack.pop_back(); stack.pop_back(); stack.pop_back(); stack.pop_back();
            SemanticObject stmt1 = stack.back();
            stack.pop_back(); stack.pop_back(); stack.pop_back();
            SemanticObject expr = stack.back();
            stack.pop_back(); stack.pop_back(); stack.pop_back();
            so.temp = "";
            std::string ifL = generateLabelToken();
            std::string elseL = generateLabelToken();
            std::string skipL = generateLabelToken();


            so.code = expr.code + "\nif(" + expr.temp + ") goto " + ifL + "\ngoto " + elseL + "\n" + ifL + ":\n" + stmt1.code + "\ngoto " + skipL + "\n" + elseL + ":\n" + stmt2.code + "\n" + skipL + ":\n";
            break;
        }
        case 22: {
            SemanticObject innerIf = stack.back();
            stack.pop_back(); stack.pop_back(); stack.pop_back();
            SemanticObject stmts = stack.back();
            stack.pop_back(); stack.pop_back(); stack.pop_back();
            SemanticObject expr = stack.back();
            stack.pop_back(); stack.pop_back(); stack.pop_back();
            
            std::string ifL = generateLabelToken();
            std::string elseL = generateLabelToken();
            std::string skipL = generateLabelToken();
            so.temp = "";
            so.code = expr.code + "\nif (" + expr.temp + ") goto " + ifL + "\ngoto " + elseL \
            + "\n" + ifL + ":\n" + stmts.code + "\ngoto " + skipL + "\n" + \
            elseL + ":\n" + innerIf.code + "\n" + skipL + ":\n";
            break;
        }
        case 23: {
            stack.pop_back();
            SemanticObject stmts = stack.back();
            stack.pop_back();
            stack.pop_back();
            stack.pop_back();
            SemanticObject expr = stack.back();
            stack.pop_back();
            stack.pop_back();
            stack.pop_back();
            so.temp = "";
            std::string ifL = generateLabelToken();
            std::string skipL = generateLabelToken();
            so.code = expr.code + "\nif (" + expr.temp + ") goto " + ifL + "\ngoto " + skipL + "\n" + ifL + ":\n" + stmts.code + "\n" + skipL + ":\n";
            break;
        }
        case 25: {
            stack.pop_back();
            SemanticObject stmts = stack.back();
            stack.pop_back(); stack.pop_back(); stack.pop_back();
            SemanticObject expr = stack.back();
            stack.pop_back(); stack.pop_back(); stack.pop_back();
            std::string whileL = generateLabelToken();
            std::string ifL = generateLabelToken();
            std::string skipL = generateLabelToken();

            so.temp = "";
            so.code = whileL + ":\n" + expr.code + "\nif (" + expr.temp + ") goto " + ifL + "\ngoto " + skipL + "\n" + ifL + ":\n" + stmts.code + "\ngoto " + whileL + "\n" + skipL + ":\n";
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
        case 46:
        toPush = false;
        break;
        case 47: {
            stack.pop_back();
            SemanticObject arg = stack.back();
            stack.pop_back(); stack.pop_back(); stack.pop_back();
            so.code = arg.code;
            break;
        }
        case 48: {
            SemanticObject args = stack.back();
            stack.pop_back(); stack.pop_back();
            SemanticObject arg = stack.back();
            stack.pop_back();
            so.code = arg.code + "\n" + args.code;
            break;
        }
        case 49: {
            SemanticObject arg = stack.back();
            stack.pop_back();
            so.code = arg.code;
            break;
        }
        case 50: {
            SemanticObject expr = stack.back();
            stack.pop_back();
            so.code = expr.code;
            break;
        }
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
            for (int i = stack.size() - toRemove; i < stack.size(); i++) {
                if (stack[i].code != "") {
                    so.code += stack[i].code + "\n";
                }
            }
            for (int i = 0; i < toRemove; i++) {
                stack.pop_back();
            }
        }
    }
    if (toPush) {
        stack.push_back(so);
    }
}

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

void printErrors(std::vector<std::vector<std::string> > &errorList){
    for(int i=0;i<errorList.size();i++){
        std::cout << "Error at line " << errorList[i][1] << ", token: " << errorList[i][2] << " of type: " << errorList[i][3] << " resolved to token: " << errorList[i][4] << std::endl;
    }
}

Parser::Parser(std::vector<Token> tokens, ParsingTableReader *ptable) {
    preader = ptable;
    tokens.push_back(Token("$", -1, "EOF", -1));
    int tokenPointer = 0;
    std::vector<std::string> stack;
    std::vector<SemanticObject> semanticStack;

    std::vector<std::vector<std::string> > errorList;
    stack.push_back("0");
    while (tokenPointer < tokens.size()) {
        Token token = tokens[tokenPointer];
        std::string tokVal = resolveTokenValue(token);
        
        auto temp = ptable->actionTable.find(make_pair(stack.back(), tokVal));
        if (temp != ptable->actionTable.end()) {
            std::string action = temp->second;
            if (action == "acc") {
                std::cout << "Parsing Successful with ";
                errorList.size() == 0 ? std::cout<<"no" : std::cout<<"some";
                std::cout<<" errors."<<std::endl;
                printErrors(errorList);
                std::cout << "\n\nThe intermediate three address code generated is:" << std::endl;
                std::cout << semanticStack.back().code << std::endl;
                return;
            }
            if (action[0] == 's') {
                printStack(stack, action);
                stack.push_back(tokVal);
                stack.push_back(action.substr(1));
                // push into semantic stack
                SemanticObject sobj = SemanticObject();
                sobj.code = "";
                sobj.temp = token.tokenString;
                semanticStack.push_back(sobj);
                tokenPointer++;
            } else if (action[0] == 'r') {
                int ruleNum = stoi(action.substr(1));
                printStack(stack, action);
                std::string nonTerminal = ptable->ruleConstants[ruleNum][0];
                int ruleLength = stoi(ptable->ruleConstants[ruleNum][1]);
                for (int i = 0; i < 2 * ruleLength; i++) {
                    stack.pop_back();
                }
                modifyStack(semanticStack, ruleNum);
                // semantic conditions
                std::string lastState = stack.back();
                // std::cout << "Last state: " << lastState << std::endl;
                stack.push_back(nonTerminal);
                std::string toPush = ptable->gotoTable[make_pair(lastState, nonTerminal)];
                printStack(stack, "goto " + toPush);
                stack.push_back(toPush);
            }
        } else {

            // handle error
            // std::cout << "Error." << std::endl;
            // std::cout << "Token: " << token.tokenString << std::endl;
            // std::cout << "Line: " << token.lineNumber << std::endl;
            // std::cout << "Token Type: " << token.type << " " << tokVal << std::endl;
            // std::cout << "State: " << stack.back() << std::endl;
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
        }
        
    }

}
