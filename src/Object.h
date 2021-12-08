/**
 * File:            Object.h
 *
 * Author:          Lincoln Scheer
 * Date Created:    11/7/21
 *
 * Purpose:         Contains the definition for the Variable and 
 *                  Rule structs
 *
 * Description:     Variables and Rules are the two objects that 
 *                  are generated by the Parser class.
 *
 * Public Structs:  Rule        -> Name, Dependencies, Commands, References, execute()
 *                  Variable    -> Name, Value
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#ifndef OBJECT_H_
#define OBJECT_H_

struct Variable {
    Variable(std::string name, std::string value) {
        this->name = name;
        this->value = value;
    }
    std::string name;
    std::string value;
};


struct Rule {
    Rule(std::string name, int definitionLine, std::vector<std::string> dependencies, std::vector<std::string> commands, std::vector<Variable> references) {
        this->name = name;
        this->definitionLine = definitionLine;
        this->dependencies = dependencies;
        this->commands = commands;
        this->references = references;
    }

    void beginReference() {
        bufferB = bufferA;
        bufferA = "";
        referenceMode = true;
    }

    void toggleReferenceDefinitionMode() {
        if(referenceDefinitionMode) {
            referenceDefinitionMode = false;
            endReference();
            displayBuffer += "\"";
        } else {
            referenceDefinitionMode = true;
        }

    }

    std::string endReference() {
       referenceMode = false;
       std::string refValue = "";

       for(auto& var : references) {
           if(bufferA == var.name) {
               refValue = var.value;
           }
       }

       bufferA = bufferB;
       displayBuffer = bufferB;
       displayBuffer += "\"";
       displayBuffer += refValue;
       bufferA += refValue;


       bufferB = "";
       return bufferA;
    }

    void execute() {
        if(!completed) {

            int commandNumber = 1;

            for(std::string& command : commands) {
            	displayBuffer = "";
            	int commandExitCode = 0;


                for(auto& character : command) {
                	if(character == '$') {
                		beginReference();
                		displayBuffer += "\"";
					} else if (character == '(' || character == ')' || character == '{' || character == '}') {
						if(referenceMode) {
							toggleReferenceDefinitionMode();
							command = bufferA;
						} else {
							bufferA += character;
							displayBuffer +=character;
						}
					} else {
						bufferA += character;
						displayBuffer += character;
					}
                }

                // Display command to execute
                std::cout << displayBuffer << std::endl;


                if(command.substr(0, 4) == "exit" || command.substr(0, 4) == "EXIT") {
                    command.erase(command.begin(), command.begin() + 5);
                    std::istringstream ( command ) >> commandExitCode;
                }else {
                    commandExitCode = system(command.c_str());
                }
                if(commandExitCode != 0) {
                    std::cout << "BuildTool:" << (commandNumber + definitionLine) << ": recipe for target \'" << name << "\' failed" << std::endl;
                    std::cout << "BuildTool: *** [" << name << "] error " << commandExitCode << std::endl;
                    exit(2);
                }
                commandNumber++;
            }
            completed = true;
        }
    }

    bool completed = false;
    bool referenceMode = false;
    bool referenceDefinitionMode = false;
    std::string bufferA = "";
    std::string bufferB = "";
    std::string displayBuffer = "";
    int definitionLine;
    std::string name;
    std::vector<std::string> dependencies;
    std::vector<std::string> commands;
    std::vector<Variable> references;
};

#endif /* OBJECT_H_ */
