#include "lexer.h"
#include "token.h"
#include "exceptions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

std::string& trim(std::string& str) {
    str = str.erase(0, str.find_first_not_of(" "));
    str = str.erase(str.find_last_not_of(" ") + 1);
    return str;
}

Lexer::Lexer(std::string inputFile) {
    tokenPointer = 0;
    newSymbolID = 1;
    initializeReservedKeywords();
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        throw FileNotFoundException(inputFile);
    }
    std::string line;
    int ln = 0;
    int state = 0;
    while (getline(file, line)) {
        line = trim(line);
        line += '\n';
        ln++;
        int linePointer = 0;
        std::string currentIntFloat = "";
        std::string currentString = "";
        while (linePointer < line.length()) {
            char c = line[linePointer];
            if ((state != 16 && c == ' ') || c == '\t' || c == '\n' || c == '\r') {
                linePointer++;
                // special cases for int/float/string
                // if it is in a valid int/float state, we add the token
                if (state == 12 || state == 13) {
                    addToken(currentIntFloat, ln, "int");
                    state = 0;
                } else if (state == 15) {
                    addToken(currentIntFloat, ln, "float");
                    state = 0;
                } else if (state == 14) {
                    // Maybe a float token but throw an error for now
                    throw LexicalException(ln, linePointer,  line, "Invalid number!");
                } else if (state == 16) {
                    // String literal contains tab, newLine, or return carriage; throw error
                    throw LexicalException(ln, linePointer, line, "Invalid string!");
                }
                currentIntFloat = "";
                continue;
            }
            switch (state) {
                ///////////////////////////////////////////////////////////////////////////////////////
                case 0: {
                    // checking if its reserved or an identifier
                    std::string firstWord = findWord(line, &linePointer);
                    if (firstWord.length() > 0) {
                        addToken(firstWord, ln, reservedKeywords.count(firstWord) ? "keyword" : "identifier");
                        break;
                    }
                    // checking if it is an int or float literal
                    // case 1: if first digit is 0
                    if (c == '0') {
                        state = 12;
                        currentIntFloat += c;
                        linePointer++;
                        break;
                    }
                    // case 2: if first digit is 1-9
                    if (c >= '1' && c <= '9') {
                        state = 13;
                        currentIntFloat += c;
                        linePointer++;
                        break;
                    }
                    // case 3: if first digit is .
                    if (c == '.') {
                        state = 14;
                        currentIntFloat += c;
                        linePointer++;
                        break;
                    }

                    // operators (part 1) (only one character and not ambiguous)
                    if (c == '*' || c == '%' || c == '?') {
                        addToken(std::string(1, c), ln, "operator");
                        linePointer++;
                        break;
                    }
                    // operators (part 2) (two characters and not ambiguous)
                    if (c == '&') { 
                        state = 1;
                        linePointer++;
                        break;
                    }
                    if (c == '|') { 
                        state = 2;
                        linePointer++;
                        break;
                    }
                    if (c == '=') { 
                        state = 3;
                        linePointer++;
                        break;
                    }
                    if (c == '>') { 
                        state = 4;
                        linePointer++;
                        break;
                    }
                    if (c == '<') { 
                        state = 5;
                        linePointer++;
                        break;
                    }
                    if (c == '!') { 
                        state = 6;
                        linePointer++;
                        break;
                    }
                    if (c == ':') { 
                        state = 7;
                        linePointer++;
                        break;
                    }
                    // delimiters
                    if (c == '{' || c == '}' || c == '(' || c == ')' || c == '[' || c == ']' || c == ';' || c == ',') {
                        linePointer++;
                        addToken(std::string(1, c), ln, "delimiter");
                        break;
                    }
                    // special case for '/' (can be an operator or start of a comment)
                    if (c == '/') {
                        state = 8;
                        linePointer++;
                        break;
                    }
                    // special case for '+' or '-' (can be an operator or start of a number)
                    if (c == '+' || c == '-') {
                        state = 0;
                        linePointer++;
                        addToken(std::string(1, c), ln, "operator/sign");
                        break;
                    }
                    // implementation of string
                    if (c == '"'){
                        state = 16;
                        currentString += '"';
                        linePointer++;
                        break;
                    }

                    // still in state 0 means invalid character 
                        throw LexicalException(ln, linePointer, line, "Invalid Character: " + std::string(1, c));


                    break;
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                case 1: {
                    if (c == '&') {
                        addToken("&&", ln, "operator");
                        linePointer++;
                        state = 0;
                        break;
                    } else {
                        // error
                        throw LexicalException(ln, linePointer, line, "Unexpected Character: " + std::string(1, c));
                    }
                  
                    break;
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                case 2: {
                    if (c == '|') {
                        addToken("||", ln, "operator");
                        linePointer++;
                        state = 0;
                        break;
                    } else {
                        // error
                        throw LexicalException(ln, linePointer, line, "Unexpected Character: " + std::string(1, c));
                    }
                }
                break;
                ///////////////////////////////////////////////////////////////////////////////////////
                case 3: {
                    if (c == '=') {
                        addToken("==", ln, "operator");
                        linePointer++;
                        state = 0;
                        break;
                    } else {
                        addToken("=", ln, "operator");
                        // we dont need to increment linePointer here
                        state = 0;
                        break;
                    }
                    break;
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                case 4: {
                    if (c == '=') {
                        addToken(">=", ln, "operator");
                        linePointer++;
                        state = 0;
                        break;
                    } else {
                        addToken(">", ln, "operator");
                        // we dont need to increment linePointer here
                        state = 0;
                        break;
                    }
                    break;
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                case 5: {
                    if (c == '=') {
                        addToken("<=", ln, "operator");
                        linePointer++;
                        state = 0;
                        break;
                    } else {
                        addToken("<", ln, "operator");
                        // we dont need to increment linePointer here
                        state = 0;
                        break;
                    }
                    break;
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                case 6: {
                    if (c == '=') {
                        addToken("!=", ln, "operator");
                        linePointer++;
                        state = 0;
                        break;
                    } else {
                        addToken("!", ln, "operator");
                        // we dont need to increment linePointer here
                        state = 0;
                        break;
                    }
                    break;
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                case 7: {
                    if (c == '=') {
                        addToken(":=", ln, "operator");
                        linePointer++;
                        state = 0;
                        break;
                    } else {
                        addToken(":", ln, "operator");
                        // we dont need to increment linePointer here
                        state = 0;
                        break;
                    }
                    break;
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                case 8: {
                    if (c == '*') {
                        // multi line comment
                        state = 9;
                        linePointer++;
                        break;
                    } else if (c == '/') {
                        // single line comment
                        state = 11;
                        linePointer++;
                        break;
                    } else {
                        addToken("/", ln, "operator");
                        // we dont need to increment linePointer here
                        state = 0;
                        break;
                    }
                    break;
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                case 9: {
                    // this is a special place where the code is currently in comment mode (/*)
                    if (c == '*') {
                        state = 10;
                        linePointer++;
                        break;
                    } else {
                        linePointer++; // just check back again with the next character (self loop in dfa)
                        break;
                    }
                    break;
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                case 10: {
                    // about to escape the comment mode /* .... *
                    if (c == '/') {
                        state = 0; // comment done
                        linePointer++;
                        break;
                    } else {
                        linePointer++; // false alarm, comment still going on
                        if (c != '*') state = 9; // go back to comment state unless the character is still '*'
                        break;
                    }
                    break;
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                case 11: {
                    // single line comment mode, only go back to state 0 if this is the last character of the line (excluding the \n)
                    if (linePointer == line.length() - 2) {
                        linePointer++; // will go to next line now
                        state = 0;
                        break;
                    } else {
                        linePointer++;
                        break;
                    }
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                // A 0 was encountered, if we encounter a . it is a floating point number otherwise its a 0
                case 12: {
                    if (c == '.') {
                        // this is the beginning of a floating point number
                        state = 14;
                        currentIntFloat += c;
                        linePointer++;
                        break;
                    } else {
                        addToken("0", ln, "int");
                        // no need to increment linePointer here
                        currentIntFloat = "";
                        state = 0;
                        break;
                    }
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                // A 1-9 int was encountered, now we can accept 0-9 or a . to begin a floating point number
                case 13: {
                    if (c >= '0' && c <= '9') {
                        // self loop on this state
                        linePointer++;
                        currentIntFloat += c;
                        break;
                    } else if (c == '.') {
                        state = 14;
                        currentIntFloat += c;
                        linePointer++;
                        break;
                    } else {
                        addToken(currentIntFloat, ln, "int");
                        currentIntFloat = "";
                        // no need to increment linePointer here
                        state = 0;
                        break;
                    }
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                // A . was encountered, now we can accept 0-9 to begin a floating point number, in other case it is an error
                case 14: {
                    if (c >= '0' && c <= '9') {
                        // this is the beginning of a floating point number
                        state = 15;
                        linePointer++;
                        currentIntFloat += c;
                        break;
                    }
                    // error

                    currentIntFloat = "";
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                // Accept [0-9]
                case 15: {
                    if (c >= '0' && c <= '9') {
                        // self loop on this state
                        linePointer++;
                        currentIntFloat += c;
                        break;
                    } else {
                        // Add the saved token and go back to state 0
                        addToken(currentIntFloat, ln, "float");
                        currentIntFloat = "";
                        // no need to increment linePointer here
                        state = 0;
                        break;
                    }
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                // A '"' (double quote) was encountered, marking the start of a string literal
                case 16: {
                    if (c != '"' && c != '\\') {
                        currentString += c;
                        linePointer++;
                        break;
                    } else if (c == '"') {  // Another double quote marks the end of the string
                        state = 0;
                        currentString += '"';
                        addToken(currentString, ln, "string");
                        currentString = "";
                        linePointer++;
                        break;
                    } else if (c == '\\') { // A backslash marks the presence of a potential escape character
                        state = 17;
                        linePointer++;
                        break;
                    }
                    break;
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                // A backslash was encountered in the string. This could potentially be an escape character
                case 17: {
                    if (c == 't') {
                        currentString += "\\t";
                        linePointer++;
                        state = 16;
                        break;
                    } else if (c == 'n') {
                        currentString += "\\n";
                        linePointer++;
                        state = 16;
                        break;
                    } else if (c == 'r') {
                        currentString += "\\r";
                        linePointer++;
                        state = 16;
                        break;
                    } else if (c == '"') {
                        currentString += '"';
                        linePointer++;
                        state = 16;
                        break;
                    } else if (c == '\\') {
                        currentString += '\\';
                        linePointer++;
                        state = 16;
                        break;
                    } else {    // Throw error if it isnt a known escape character
                        throw LexicalException(ln, linePointer, line, "Invalid string!");
                    }
                }
                ///////////////////////////////////////////////////////////////////////////////////////
                default:
                break;
            }
        }
    }
}

void Lexer::initializeReservedKeywords() {
    std::string reserved[] = {
        "int",
        "float",
        "boolean",
        "string",
        "while",
        "until",
        "if",
        "else",
        "true",
        "false",
        "return"
    };
    for (const std::string str: reserved) {
        reservedKeywords.insert(str);
        symbolTable[str] = newSymbolID++;   // Adding keywords to symbol table, ID starting from 1
    }
    newSymbolID = 101;  // IDs for other tokens starting from 101
}

std::string Lexer::findWord(std::string input, int *linePointer) {
    std::string word = "";
    char firstChar = input[*linePointer];
    while (*linePointer < input.length()) {
        char c = input[*linePointer];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || ((c >= '0' && c <= '9') && firstChar != c)) {
            word += c;
            (*linePointer)++;
        } else {
            break;
        }
    }
    return word;
}

void Lexer::addToken(std::string token, int line, std::string type) {
    // Checking if current token has an entry in symbol table. If not, creating new entry.
    if (symbolTable.find(token) == symbolTable.end()) symbolTable[token] = newSymbolID++;
    Token t = Token(token, line, type, symbolTable[token]);
    tokens.push_back(t);
}

Token* Lexer::getNextToken() {
    if (tokenPointer < tokens.size()) {
        return &tokens[tokenPointer++];
    } else {
        return NULL;
    }
}