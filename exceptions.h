#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

class FileNotFoundException {
    std::string fileName;
    public:
        FileNotFoundException(std::string fileName);
        std::string getFileName();
};

class LexicalException {
    int lineNumber;
    int linePointer;
    std::string message;
    std::string line;
    public:
        LexicalException(int lineNumber, int linePointer, std::string line, std::string message);
        int getLineNumber();
        int getLinePointer();
        std::string getMessage();
        std::string getLine();
};


#endif