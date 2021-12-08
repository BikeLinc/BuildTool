/**
 * File:            Compiler.cpp
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
 *                  executeAllRules()   -> Execute all rules in order based on dependencies
 *                  executeRule()       -> Execute specific rule and dependencies
 *
 */

#include "Compiler.h"
#include "Object.h"


Compiler::Compiler(std::vector<Rule> rules) {
    this->rules = rules;
}

void Compiler::execute(const int argc, const char** argv) {
	if(argc == 2) {
        executeRule(argv[1]);
    // Execute all rules and dependencies
    } else {
        executeAllRules();
    }
}

void Compiler::executeAllRules() {
    if(rules.size() == 0) {
        std::cout << "fake: *** No targets. Stop." << std::endl;
        exit(2);
    }
    
	bool complete = false;
	
    while(!complete) {

		// Execute all ready rules
		for(Rule rule : rules) {
			if(isReady(rule)) {
				rule.execute();
				completed.push_back(rule);
			}
		}

		// Detect circular dependencies
		if(completed.empty()) {
			std::cout << "fake: Circular " << rules.back().name << " <- " << rules.back().dependencies.front() << " dependency dropped." << std::endl;
			rules.back().dependencies.erase(rules.back().dependencies.begin());
		}


		// Mark complete when all rules done
		if(completed.size() == rules.size()) {
			complete = true;
		}
	}
}

// Execute individual rule
void Compiler::executeRule(std::string rule) {
    if(rules.size() == 0) {
        std::cout << "fake: *** No targets. Stop." << std::endl;
        exit(2);
    }
    bool present = false;

    for(auto& rulePresent : rules) {
        if(rulePresent.name == rule) {
            rulePresent.execute();
            present = true;
            break;
        }
    }   
    if(!present) {
        std::cout << "fake: Target \'" << rule << "\' does not exits. Stop." << std::endl;

    }
}

bool Compiler::isDependenciesResolved(Rule rule) {
    bool depsComplete = true;
    for(auto& dep : rule.dependencies) {
    	checkRuleExists(dep, rule.name);
        if(!isRuleCompleted(dep)) {
            depsComplete = false;
        }
    }
    return depsComplete;
}

bool Compiler::checkRuleExists(std::string ruleName, std::string caller) {
	bool ruleDefinitionPresent = false;

	for(auto& definedRule : rules) {
		if(ruleName == definedRule.name) {
			ruleDefinitionPresent = true;
		}
	}
	if(!ruleDefinitionPresent) {
		std::cout << "fake: *** No rule to make target \'" << ruleName << "\', needed by \'" << caller << "\'. Stop." << std::endl;
		std::vector<std::string> empty;
		std::vector<Variable> vars;
		Rule rule(caller,0, empty, empty, vars);
		exit(2);
	}
	return ruleDefinitionPresent;
}

bool Compiler::isRuleCompleted(std::string rule) {
    for(auto& completedRule : completed) {
        if(rule == completedRule.name) {
            return true;
        }
    }
    return false;
}

bool Compiler::isReady(Rule rule) {
	return (!isRuleCompleted(rule.name) && isDependenciesResolved(rule));
}



