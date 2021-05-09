#pragma once
#include "reactant.h"
#include "rule.h"
#include <string>
#include <vector>
#include <iostream>

class vessel_t
{
public:
	vessel_t() = default;

	std::vector<reactant> environment() {
		return env;
	};

	// Initalize Reactant
	std::vector<reactant> operator()(std::string reactant_identifier, int quantity) {
		reactants.push_back(reactant(reactant_identifier, quantity));
		return std::vector<reactant>{reactant(reactant_identifier, quantity)};
	};

	// Constructor with environment, reactants and time
	std::vector<reactant> operator()(const std::vector<reactant>& env, const std::vector<reactant> reactants, double time) {
		return env;
	};

	// Constructor for rule
	rule operator()(const std::vector<std::vector<reactant>>& reaction_pair, double time) {
		rules.push_back(rule{ reaction_pair.front(), reaction_pair.back(), time });
		return rule{ reaction_pair.front(), reaction_pair.back(), time };
	};

	// Secondary constructor for rule
	rule operator()(const std::vector<std::vector<reactant>>& reaction_pair, const std::vector<reactant> catalyst, double time) {
		rules.push_back(rule{ reaction_pair.front(), reaction_pair.back(), catalyst, time });
		return rule{reaction_pair.front(), reaction_pair.back(), catalyst, time};
	};

private:
	std::vector<reactant> reactants;
	std::vector<reactant> env;
	std::vector<rule> rules;
};


