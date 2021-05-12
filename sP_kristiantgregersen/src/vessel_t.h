#pragma once
#include "reactant.h"
#include "rule.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "node.h"
#include <fstream>
#include <string>
#include <iostream>
#include <set>

using std::string;
using std::vector;
class vessel_t
{
public:
	vessel_t() = default;

	vector<reactant> environment();

	// Initalize Reactant
	vector<reactant> operator()(string reactant_identifier, int quantity);

	// Constructor with environment, reactants and time
	vector<reactant> operator()(const vector<reactant> env, const vector<reactant> reactants, double time);

	// Constructor for rule
	rule operator()(const vector<vector<reactant>> reaction_pair, double time);

	// Secondary constructor for rule
	rule operator()(const vector<vector<reactant>> reactio_input_output, const vector<reactant> catalyst, double time);

	vector<reactant> getReactants() const;
	vector<rule>& getReactionRules();
	string buildReactionGraph();

private:
	vector<reactant> _reactants;
	vector<reactant> _env;
	vector<rule> _rules;

	std::tuple<string, vector<node>> buildNodeString(string graphId, string fillcolor, string shape);
	std::string buildRuleString(std::vector<node> nodes, std::string graphId, std::string fillcolor, std::string shape);
};




