#pragma once
#include <list>
#include <string>
#include <vector>
#include "reaction_rule.h"

class reactant
{
private: 
	std::string _identifier;
	int _quantity;

public:
	reactant() = default;
	reactant(std::string identifier, int initial_quantity) : _identifier(identifier), _quantity(initial_quantity) {}

	friend std::vector<reactant> operator+(std::vector<reactant> lhs, std::vector<reactant> const& rhs) {
		return std::vector<reactant>{(rhs, lhs)};
	};

	friend std::vector<std::vector<reactant>> operator>>=(std::vector<reactant> input, std::vector<reactant> const& output) {
		return std::vector<std::vector<reactant>>{(input, output)};
	}
};

