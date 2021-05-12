#include "vessel_t.h"

vector<Reactant> vessel_t::environment()
{
	return _env;
}
vector<Reactant> vessel_t::operator()(string reactant_identifier, int quantity)
{
	_reactants.push_back(Reactant(reactant_identifier, quantity));
	return vector<Reactant>{Reactant(reactant_identifier, 1)};
};

vector<Reactant> vessel_t::operator()(const vector<Reactant> env, const vector<Reactant> reactants, double time) {
	return env;
};

ReactionRule vessel_t::operator()(const vector<vector<Reactant>> reaction_pair, double time) {
	_rules.push_back(ReactionRule{ reaction_pair.front(), reaction_pair.back(), time });
	return ReactionRule{ reaction_pair.front(), reaction_pair.back(), time };
};

ReactionRule vessel_t::operator()(const vector<vector<Reactant>> reactio_input_output, const vector<Reactant> catalyst, double time) {
	_rules.push_back(ReactionRule{ reactio_input_output.front(), reactio_input_output.back(), catalyst, time });
	return ReactionRule{ reactio_input_output.front(), reactio_input_output.back(), catalyst, time };
}
vector<Reactant> vessel_t::getReactants() const
{
	return _reactants;
}
vector<ReactionRule>& vessel_t::getReactionRules()
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