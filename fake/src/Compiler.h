/**
 * File:            Compiler.h
 *
 * Author:          Chloe Walsh
 * Date Created:    11/7/21
 *
 * Purpose:         Facilitate the preparation and execution of Rules
 *
 * Description:     To prepare rules for execution, the compiler identifies references
 *                  and substitues the variable value before making the system(command)
 *                  call.
 *
 * Public Methods:  Compiler()          -> Set the member rules variable to paramater input
 *                  execute()           -> Call the correct execute method based on command line arguments    
 *                  executeAllRules()   -> Execute all rules in order based on dependencies
 *                  executeRule()       -> Execute specific rule and dependencies
 *
 */

#ifndef COMPILER_H
#define COMPILER_H

#include "Object.h"

class Compiler {
    
    public:
        Compiler(std::vector<Rule> rules);
        void execute(const int argc, const char** argv);
        void executeAllRules();
        void executeRule(std::string rule);
    private:
        std::vector<Rule> rules;
        std::vector<Rule> completed; 
        bool isDependenciesResolved(Rule rule);
        bool checkRuleExists(std::string rule, std::string caller);
        bool isRuleCompleted(std::string rule);
        bool isReady(Rule rule);
};

#endif /* COMPILER_H */
