#include "exceptions.h"
#include <iostream>

//fuction for handling File not found exceptions
FileNotFoundException::FileNotFoundException(std::string fileName) {
    this->fileName = fileName;
}

std::string FileNotFoundException::getFileName() {
    return fileName;
}


//fuction for handling lexical exceptions
LexicalException::LexicalException(int lineNumber, int linePointer, std::string line, std::string message) {
    this->lineNumber = lineNumber;      // line number of code where an error is encountered
    this->linePointer = linePointer;    // index of a character which caused the error
    this->message = message;            // error message
    this->line = line;                  //error line
}

//respective constructors
int LexicalException::getLineNumber() {
    return lineNumber;
}

int LexicalException::getLinePointer() {
    return linePointer;
}

std::string LexicalException::getMessage() {
    return message;
}

std::string LexicalException::getLine() {
    return line;
}