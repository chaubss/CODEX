#ifndef PARSINGTABLEREADER_H
#define PARSINGTABLEREADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class ParsingTableReader {

    public:
        std::vector<std::string> terminals;
        std::vector<std::string> nonTerminals;
        std::map<std::pair<std::string, std::string>, std::string> actionTable;
        std::map<std::pair<std::string, std::string>, std::string> gotoTable;
        std::string ruleConstants[100][2] = {
            { "PROGRAM", "1" },
            { "STMTS", "2" },
            { "STMTS", "0" },
            { "STMT", "1" },
            { "STMT", "1" },
            { "STMT", "1" },
            { "STMT", "2" },
            { "STMT", "2" },
            { "STMT", "2" },
            { "STMT", "2" },
            { "DEFN", "2" },
            { "DEFN_LIST", "3" },
            { "DEFN_LIST", "1" },
            { "ID_MAYBE_INIT", "1" },
            { "ID_MAYBE_INIT", "3" },
            { "FUNC", "8" },
            { "ARGS", "3" },
            { "ARGS", "1" },
            { "ARG", "2" },
            { "ARG", "0" },
            { "IF", "11" },
            { "IF", "7" },
            { "WHILE", "7" },
            { "RETURN", "2" },
            { "ASSIGN", "3" },
            { "EXPR", "3" },
            { "EXPR", "1" },
            { "TERM", "3" },
            { "TERM", "1" },
            { "TERM2", "3" },
            { "TERM2", "1" },
            { "TERM3", "3" },
            { "TERM3", "1" },
            { "TERM3", "1" },
            { "FUNC_CALL", "4" },
            { "FUNC_ARGS", "3" },
            { "FUNC_ARGS", "1" },
            { "FUNC_ARG", "1" },
            { "FUNC_ARG", "0" },
            { "TYPE", "1" },
            { "TYPE", "1" },
            { "TYPE", "1" },
            { "TYPE", "1" },
            { "TYPE", "1" },
            { "TYPE", "1" },
            { "OP1", "1" },
            { "OP1", "1" },
            { "OP2", "1" },
            { "OP2", "1" },
            { "OP3", "1" },
            { "OP3", "1" },
            { "OP3", "1" },
            { "OP3", "1" },
            { "OP3", "1" },
            { "OP3", "1" },
            { "ID", "1" }
        };
        ParsingTableReader(std::string actionFileName, std::string gotoFileName);


};

#endif