/**
 * File:            Parser.h
 *
 * Author:          Chloe Walsh
 * Date Created:    11/7/21
 *
 * Purpose:         Itentify symbols in a Fakefile and generate a
 *                  list of Rules and Variables.
 *
 * Description:     To generate a list of symbols this class first
 *                  loops through all characters in the file and
 *                  detects specific symbols (=, ", : ,$, ( or ), { or })
 *
 * Public Methods:  Parser(filepath)    -> Generates all symbols found in file
 *                  getVariables()      -> Returns a std::vector of variables generated
 *                  getRules()          -> Returns a std::vector of rules generated
 *
 */

#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include "Object.h"

class Parser {
public:
    Parser(const char* filepath);
    std::vector<Variable> getVariables();
    std::vector<Rule> getRules();
private:
    // Generated Variables and Rules are pushed into these arrays
    std::vector<Variable> variables;
    std::vector<Rule> rules;

    // Buffers used to store data temporarily while generating Variables and Rules
    std::string bufferA = "";
    std::string bufferB = "";
    std::string ruleBuffer = "";
    std::string depsBuffer = "";
    std::vector<std::string> commandBuffer;

    // Flags used to tell the parser how to act based on which context flags are set
    bool variableMode = false;
    bool valueMode = false;
    bool ruleMode = false;
    bool referenceMode = false;
    bool referenceDefinitionMode = false;

    // Integers to keep track of the current line and the Rule definition line
    int definitionLine = 0;
    int currentLine = 1;

    // All parsing happens in this function, it just calls the helper functions below
    void parse(const char* filepath);

    // Buffer Manipulation
    void addCharToBuffer(char character);
    void storeBufferAinB();

    // Variable creation
    void beginVariable();
    void endVariable();
    void toggleValueMode();
    
    // Rule creation
    void beginRule();
    void endRule();
    void addCommand();
    void addDependencies();

};

#endif /* PARSER_H */