#include "exceptions.h"
#include <iostream>

FileNotFoundException::FileNotFoundException(std::string fileName) {
    this->fileName = fileName;
}

std::string FileNotFoundException::getFileName() {
    return fileName;
}

LexicalException::LexicalException(int lineNumber, std::string line, std::string message) {
    this->lineNumber = lineNumber;
    this->message = message;
    this->line = line;
}

int LexicalException::getLineNumber() {
    return lineNumber;
}

std::string LexicalException::getMessage() {
    return message;
}

std::string LexicalException::getLine() {
    return line;
}