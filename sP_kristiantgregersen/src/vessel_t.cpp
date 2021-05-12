#include "vessel_t.h"

vector<reactant> vessel_t::environment()
{
	return _env;
}
vector<reactant> vessel_t::operator()(string reactant_identifier, int quantity)
{
	_reactants.push_back(reactant(reactant_identifier, quantity));
	return vector<reactant>{reactant(reactant_identifier, 1)};
};

vector<reactant> vessel_t::operator()(const vector<reactant> env, const vector<reactant> reactants, double time) {
	return env;
};

rule vessel_t::operator()(const vector<vector<reactant>> reaction_pair, double time) {
	_rules.push_back(rule{ reaction_pair.front(), reaction_pair.back(), time });
	return rule{ reaction_pair.front(), reaction_pair.back(), time };
};

rule vessel_t::operator()(const vector<vector<reactant>> reactio_input_output, const vector<reactant> catalyst, double time) {
	_rules.push_back(rule{ reactio_input_output.front(), reactio_input_output.back(), catalyst, time });
	return rule{ reactio_input_output.front(), reactio_input_output.back(), catalyst, time };
}
vector<reactant> vessel_t::getReactants() const
{
	return _reactants;
}
vector<rule>& vessel_t::getReactionRules()
{
	return _rules;
}
string vessel_t::buildReactionGraph()
{
	string output = "digraph {";
	auto i = 0;

	auto [returnString, nodes] = (buildNodeString("s", "cyan", "box"));
	output.append(returnString);
	output.append(buildRuleString(nodes, "r", "yellow", "oval"));
	output.append("}");

	std::ofstream file("graph.dot");
	file << output;

	return output;
}

std::tuple<string, vector<node>> vessel_t::buildNodeString(string graphId, string fillcolor, string shape) {
	int i = 0;
	std::stringstream nodeString;
	vector<node> nodes;

	for (const auto& reactant : _reactants)
	{
		string nodeId = "s";
		nodeId.append(std::to_string(i));
		nodes.push_back(node{ reactant.getQuanitity(), nodeId, reactant.getIdentifier() });
		nodeString << nodeId << "[label=\"" << reactant.getIdentifier() << "\",shape=\"" << shape << "\",style=\"filled\",fillcolor=\"" << fillcolor << "\"];" << std::endl;
		i++;
	}

	return  { nodeString.str(), nodes };
};

std::string vessel_t::buildRuleString(std::vector<node> nodes, std::string graphId, std::string fillcolor, std::string shape) {

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
;