#include "ptable_reader.h"
#include "exceptions.h"
#include <iostream>
#include <string>

ParsingTableReader::ParsingTableReader(std::string actionFileName, std::string gotoFileName) {

    std::ifstream actionFile(actionFileName);
    if (!actionFile.is_open()) {
        throw FileNotFoundException(actionFileName);
    }

    std::ifstream gotoFile(gotoFileName);
    if (!gotoFile.is_open()) {
        throw FileNotFoundException(gotoFileName);
    }
    std::string line, terminal="";
    actionFile >> line;
    for(int i = 0; i < line.length(); i++) {
        if(line[i] != ',') {
            terminal += line[i];
        }
        if (line[i] == ',') {
            if(terminal.length() > 0) {
                terminals.push_back(terminal);
                terminal = "";
            }
        } else if (i < line.length() - 1 && line[i] == '"' && line[i + 1] == ','){
            terminals.push_back(",");
            terminal = "";
            i += 2;
        }
    }
    if (terminal.length() > 0) {
        terminals.push_back(terminal);
    }
    std::string nonTerminal = "";
    gotoFile >> line;
    for(int i = 0; i < line.length(); i++) {
        if(line[i] != ',') {
            nonTerminal += line[i];
        }
        if (line[i] == ',') {
            if(nonTerminal.length() > 0) {
                nonTerminals.push_back(nonTerminal);
                nonTerminal = "";
            }
        } else if (i < line.length() - 1 && line[i] == '"' && line[i + 1] == ','){
            nonTerminals.push_back(",");
            nonTerminal = "";
            i += 2;
        }
    }
    if (nonTerminal.length() > 0) {
        nonTerminals.push_back(nonTerminal);
    }
    
    // print all terminals
    // cout << "Terminals: ";
    // for(int i = 0; i < terminals.size(); i++) {
    //     cout << terminals[i] << " ";
    // }
    // cout << endl;
    // // print all non terminals
    // cout << "Non-Terminals: ";
    // for(int i = 0; i < nonTerminals.size(); i++) {
    //     cout << nonTerminals[i] << " ";
    // }
    // cout << endl;

    while (actionFile >> line) {
        std::string action = "";
        std::vector<std::string> actions;
        for(int i = 0; i < line.length(); i++) {
            if(line[i] != ',') {
                action += line[i];
            }
            if (line[i] == ',') {
                actions.push_back(action);
                action = "";
            }
        }
        actions.push_back(action);
        std::string state = actions[0];
        for (int i = 1; i < actions.size(); i++) {
            std::string action = actions[i];
            if (action.length() == 0) {
                continue;
            }
            // actionTable[ { state, terminals[i] } ] = action;
            actionTable[make_pair(state, terminals[i])] = action;
        }
    }

    while (gotoFile >> line) {
        std::string _goto = "";
        std::string state = "";
        std::vector<std::string> gotos;
        for(int i = 0; i < line.length(); i++) {
            if(line[i] != ',') {
                _goto += line[i];
            }
            if (line[i] == ',') {
                gotos.push_back(_goto);
                _goto = "";
            }
        }
        gotos.push_back(_goto);
        state = gotos[0];
        for (int i = 1; i < gotos.size(); i++) {
            std::string _gotoInside = gotos[i];
            if (_gotoInside.length() == 0) {
                continue;
            }
            // gotoTable[{state, terminals[i]}] = _gotoInside;
            gotoTable[make_pair(state, nonTerminals[i])] = _gotoInside;
        }
    }

    gotoFile.close();
    actionFile.close();
}