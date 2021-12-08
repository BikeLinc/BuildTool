/**
 * File:            Parser.cpp
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

#include "Parser.h"

// Trigger parser() with filepath
Parser::Parser(const char* filepath) {
    parse(filepath);
}


// All parsing happens in this function, it just calls the helper functions below
void Parser::parse(const char* filepath) {
    std::ifstream file(filepath);
    std::string str;

    if(!file.is_open()) {
        std::cout << "fake: *** No targets specified and no Fakefile found. Stop." << std::endl;
        exit(2);
    }

    // Loops Every Line
    while (std::getline(file, str)) {

        if(str == "") {
            endRule();
        } else {
            for(auto character : str) {
                if(isprint(character)) {
                    if(character == '=' && !variableMode && !ruleMode) {
                        endRule();
                        beginVariable();
                    } else if(character == 34 && variableMode) {
                        toggleValueMode();
                    } else if(character == ':' && !ruleMode) {
                        endRule();
                        beginRule();
                    } else if((character == ' ' && ruleMode) || (character == ' ' && valueMode)) {
                        addCharToBuffer(character);
                    }
                    /*
                    else if(character == '$') {
                        beginReference();
                    } else if (character == '(' || character == ')' || character == '{' || character == '}') {
                        if(referenceMode) {
                            toggleReferenceDefinitionMode();
                        } else {
                            addCharToBuffer(character);
                        }
                    }
                    */
                    else {
                        if(character != ' ') {
                            addCharToBuffer(character);
                        }
                    }
                    addDependencies();
                }
            }
        }
        addCommand();
        currentLine++;
    }
    endRule();
}

std::vector<Variable> Parser::getVariables() {
    return variables;
}

std::vector<Rule> Parser::getRules() {
    return rules;
}

// ==== Buffer Manipulation ====

void Parser::addCharToBuffer(char character) {
    bufferA += character;
}

void Parser::storeBufferAinB() {
    bufferB = bufferA;
    bufferA = "";
}

void Parser::beginVariable() {
    storeBufferAinB();
    variableMode = true;
}

void Parser::toggleValueMode() {
    if(!valueMode) {
        // Begin defining value
        valueMode = true;
    // If currently defining value
    } else if(valueMode) {
        // Stop variable building mode
        // Stop defining value
        variableMode = false;
        valueMode = false;
        // Create Variable
        endVariable();
    }
}

void Parser::endVariable() {
    Variable variable(bufferB, bufferA);
    // Add to list
    variables.push_back(variable);
    // Empty buffers
    bufferB = "";
    bufferA = "";
}

void Parser::beginRule() {
    ruleMode = true;
    // Set this line as definition line
    definitionLine = currentLine;
    // Move A to RuleBuffer and free A
    ruleBuffer = bufferA;
    bufferA = "";
}

void Parser::endRule() {
    if(ruleMode) {
        ruleMode = false;
        std::vector<std::string> deps;
        std::string dep = "";
        for(int i = 0; i < depsBuffer.size(); i++) {
            char character = depsBuffer[i];
            if(character != ' ') {
                dep += character;
            } else {
                if(dep != "") {
                    deps.push_back(dep);
                    dep = "";
                }
            }
        }
        if(dep != "") {
            deps.push_back(dep);
            dep = "";
        }
        Rule rule(ruleBuffer, definitionLine, deps, commandBuffer, variables);
        rules.push_back(rule);
        ruleBuffer = "";
        depsBuffer = "";
        commandBuffer.clear();
    }
}

void Parser::addCommand() {
    if(ruleMode) {
            std::string filteredCommand = "";
            for(int i = 0; i < bufferA.size(); i++) {
                char character = bufferA[i];
                if(filteredCommand == "" && character == ' ') {
                    // Do Nothing
                } else {
                    filteredCommand += character;
                }
            }
            if(filteredCommand != "") {
                commandBuffer.push_back(filteredCommand);
            }
            bufferA = "";
        }
}

void Parser::addDependencies() {
    if(ruleMode && (definitionLine == currentLine)){
        if(depsBuffer == "" && bufferA == " ") {
            bufferA = "";
        } else {
            depsBuffer += bufferA;
            bufferA = "";
        }
    }
}
