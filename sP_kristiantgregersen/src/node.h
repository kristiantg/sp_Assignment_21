#pragma once
#include <string>

// Simple node class. Used to keep track of nodes, in graph-visualization of assignment 3.
class node
{
public:
	std::string node_identifier;
	std::string reactant_identifier;
	int reactant_quantity;

	node(int _reactant_quantity, std::string _node_identifier, std::string _reactant_identifier) : node_identifier(_node_identifier), reactant_quantity(_reactant_quantity), reactant_identifier(_reactant_identifier) {}
};

