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

	vector<reactant> environment() {
		return _env;
	};

	// Initalize Reactant
	vector<reactant> operator()(string reactant_identifier, int quantity) {
		_reactants.push_back(reactant(reactant_identifier, quantity));
		return vector<reactant>{reactant(reactant_identifier, 1)};
	};

	// Constructor with environment, reactants and time
	vector<reactant> operator()(const vector<reactant> env, const vector<reactant> reactants, double time) {
		return env;
	};

	// Constructor for rule
	rule operator()(const vector<vector<reactant>> reaction_pair, double time) {
		_rules.push_back(rule{ reaction_pair.front(), reaction_pair.back(), time });
		return rule{ reaction_pair.front(), reaction_pair.back(), time };
	};

	// Secondary constructor for rule
	rule operator()(const vector<vector<reactant>> reactio_input_output, const vector<reactant> catalyst, double time) {
		_rules.push_back(rule{ reactio_input_output.front(), reactio_input_output.back(), catalyst, time });
		return rule{ reactio_input_output.front(), reactio_input_output.back(), catalyst, time };
	};

	string printReactions() {

	}

	// Build Graph
	string buildReactionGraph() {
		vector<node> nodes;
		string output = "digraph {";
		auto s = "s";
		auto r = "r";
		auto i = 0;

		for (const auto& reactant : _reactants)
		{
			string nodeId = "s";
			nodeId.append(std::to_string(i));
			nodes.push_back(node{ reactant.getQuanitity(), nodeId, reactant.getIdentifier() });
			output.append(buildNodeString(s, i, reactant.getIdentifier(), "cyan", "box"));
			i++;
		}

		output.append(buildRuleString(nodes, r, "yellow", "oval"));
		output.append("}");

		std::ofstream file("graph.dot");
		file << output;

		return output;
	}

	// Helper for build graph
	string buildNodeString(string graphId, int labelNumber, string label, string fillcolor, string shape) {

		string nodeId = graphId;
		nodeId.append(std::to_string(labelNumber));
		std::stringstream nodeString;

		nodeString << nodeId << "[label=\"" << label << "\",shape=\"" << shape << "\",style=\"filled\",fillcolor=\"" << fillcolor << "\"];" << std::endl;
		return nodeString.str();
	};

	// Helper for build graph
	std::string buildRuleString(std::vector<node> nodes, std::string graphId, std::string fillcolor, std::string shape) {

		std::stringstream nodeString;
		int i = 0;

		for (auto& rule : _rules)
		{
			auto nodeIdentifier = graphId;
			nodeIdentifier.append(std::to_string(i));
			nodeString << nodeIdentifier << "[label=\"" << rule.getTime() << "\",shape=\"" << shape << "\",style=\"filled\",fillcolor=\"" << fillcolor << "\"];" << std::endl;

			for (auto& reactant : rule.getCatalysts())
			{
				for (auto& node : nodes) {
					if (node.reactant_identifier == reactant.getIdentifier()) {
						nodeString << node.node_identifier << " -> " << nodeIdentifier << "[arrowhead=\"tee\"];" << std::endl;
					}
				}
			}

			for (auto& reactant : rule.getInput())
			{
				for (auto& node : nodes) {
					if (node.reactant_identifier == reactant.getIdentifier()) {
						nodeString << node.node_identifier << " -> " << nodeIdentifier << std::endl;
					}
				}
			}

			for (auto& reactant : rule.getOutput())
			{
				for (auto& node : nodes) {
					if (node.reactant_identifier == reactant.getIdentifier()) {
						nodeString << nodeIdentifier << " -> " << node.node_identifier << std::endl;
					}
				}
			}
			i++;
		}

		return nodeString.str();
	};

	void doStochaticSimulation(double T) {
		vector<double> delays;

		double t = 0;
		while (t <= T)
		{
			rule leastDelayRule;
			double leastDelay = 100000;

			for (auto& rule : _rules) {
				int totalQuantity = 1;
				for (auto& input : rule.getInput()) {
						totalQuantity *= getQuantity(input.getIdentifier(), _reactants);
				};

				for (auto& catalyst : rule.getCatalysts()) {
					totalQuantity *= getQuantity(catalyst.getIdentifier(), _reactants);
				};

				double currentDelay = rule.getDelay(totalQuantity, rule.getTime());
				if (currentDelay < leastDelay) {
					leastDelay = currentDelay;
					leastDelayRule = rule;
				}
			}
			t += leastDelay;

			bool isEnoughQuanity = true;

			isEnoughQuanity = hasEnoughQuantities(leastDelayRule.getInput());
			isEnoughQuanity &= hasEnoughQuantities(leastDelayRule.getCatalysts());

			if (isEnoughQuanity) {
				for (auto& ruleInput : leastDelayRule.getInput()) {
					changeQuantity(ruleInput.getIdentifier(), _reactants, -ruleInput.getQuanitity());
				}
				for (auto& ruleOutput : leastDelayRule.getOutput()) {
					changeQuantity(ruleOutput.getIdentifier(), _reactants, ruleOutput.getQuanitity());
				}
			}
			std::cout << "Tiden: " << t << " " << "A:" << getQuantity("A", _reactants) << " MA: " << getQuantity("MA", _reactants) << std::endl;
		}
	}

	bool hasEnoughQuantities(vector<reactant>& input) {
		bool isEnoughQuanity = true;
		for (auto& ruleInput : input) {
			if (ruleInput.getQuanitity() > getQuantity(ruleInput.getIdentifier(), _reactants)) {
				isEnoughQuanity = false;
			}
		}
		return isEnoughQuanity;
	}

	void changeQuantity(string reactantId, vector<reactant>& state, int ruleQuantity) {
		for (auto& reactorState : state) {
			bool isSameReactant = reactorState.getIdentifier() == reactantId;

			if (isSameReactant) {
				reactorState.setQuantity(reactorState.getQuanitity() + ruleQuantity);
			}
		}
	}

	int getQuantity(string reactantId, vector<reactant>& state) {
		for (auto& reactorState : state) {
			bool isSameReactant = reactorState.getIdentifier() == reactantId;

			if (isSameReactant) {
				return reactorState.getQuanitity();
			}
		}

		return 0;
	}

private:
	vector<reactant> _reactants;
	vector<reactant> _env;
	vector<rule> _rules;
};




