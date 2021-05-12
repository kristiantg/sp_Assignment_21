#pragma once
#include "reactant.h"
#include "ReactionRule.h"
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

	vector<Reactant> environment();

	// Initalize Reactant
	vector<Reactant> operator()(string reactant_identifier, int quantity);

	// Constructor with environment, reactants and time
	vector<Reactant> operator()(const vector<Reactant> env, const vector<Reactant> reactants, double time);

	// Constructor for rule
	ReactionRule operator()(const vector<vector<Reactant>> reaction_pair, double time);

	// Secondary constructor for rule
	ReactionRule operator()(const vector<vector<Reactant>> reactio_input_output, const vector<Reactant> catalyst, double time);

	vector<Reactant> getReactants() const;
	vector<ReactionRule>& getReactionRules();
	string buildReactionGraph();

private:
	vector<Reactant> _reactants;
	vector<Reactant> _env;
	vector<ReactionRule> _rules;

	std::tuple<string, vector<node>> buildNodeString(string graphId, string fillcolor, string shape);
	std::string buildRuleString(std::vector<node> nodes, std::string graphId, std::string fillcolor, std::string shape);
};




