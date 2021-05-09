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
	rule operator()(const std::vector<std::vector<reactant>>& reactio_input_output, const std::vector<reactant> catalyst, double time) {
		rules.push_back(rule{ reactio_input_output.front(), reactio_input_output.back(), catalyst, time });
		return rule{ reactio_input_output.front(), reactio_input_output.back(), catalyst, time};
	};

	// Build Graph
	friend std::string buildReactionGraph() {
		std::string output;
		
		return output;
	}
	
	friend std::string buildNode(int labelNumber, std::string label, std::string fillcolor, std::string shape) {
		std::string nodeString = "s0[label=\"S\",shape=\"box\",style=\"filled\",fillcolor=\"cyan\"];";
		std::string message = std::format("The answer is {}.", 42);
		return nodeString;
	};

private:
	std::vector<reactant> reactants;
	std::vector<reactant> env;
	std::vector<rule> rules;
};


