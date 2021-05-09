#pragma once
#include "../reactant.h"
#include <string>
#include <vector>
#include "../reaction_rule.h"

class vessel_t
{
public:
	vessel_t() = default;

	std::vector<reactant> reactants;
	std::vector<reactant> env;
	//std::vector<reaction_rule> rules;

	std::vector<reactant> environment() {
		return env;
	};

	// Initalize Reactant
	std::vector<reactant> operator()(std::string reactant_identifier, int quantity) {
		return std::vector<reactant>{reactant(reactant_identifier, quantity)};
	};

	// Constructor with environment, reactants and time
	std::vector<reactant> operator()(const std::vector<reactant>& env, const std::vector<reactant> reactants, double time) {
		return env;
	};

	std::vector<reactant> operator()(const std::vector<std::vector<reactant>>& reaction_pair, double time) {
		return env;
	};

	std::vector<reactant> operator()(const std::vector<std::vector<reactant>>& reaction_pair, const std::vector<reactant> catalyst, double time) {
		return env;
	};

private:

};