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
	std::string buildReactionGraph() {
		std::vector<node> nodes;
		std::string output = "digraph {";
		std::string s = "s";
		std::string r = "r";
		int i = 0;

		for (const auto& reactant : reactants)
		{
			std::string nodeId = "s";
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
	std::string buildNodeString(std::string graphId, int labelNumber, std::string label, std::string fillcolor, std::string shape) {

		std::string nodeId = graphId;
		nodeId.append(std::to_string(labelNumber));
		std::stringstream nodeString;

		nodeString << nodeId << "[label=\"" << label << "\",shape=\"" << shape << "\",style=\"filled\",fillcolor=\"" << fillcolor << "\"];" << std::endl;
		return nodeString.str();
	};

	// Helper for build graph
	std::string buildRuleString(std::vector<node> nodes, std::string graphId, std::string fillcolor, std::string shape) {

		std::stringstream nodeString;
		int i = 0;

		for (auto& rule : rules)
		{
			std::string nodeIdentifier = graphId;
			nodeIdentifier.append(std::to_string(i));
			nodeString << nodeIdentifier << "[label=\"" << rule.getTime() << "\",shape=\"" << shape << "\",style=\"filled\",fillcolor=\"" << fillcolor << "\"];" << std::endl;
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

private:
	std::vector<reactant> reactants;
	std::vector<reactant> env;
	std::vector<rule> rules;
};




