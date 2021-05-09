#pragma once
#include <list>
#include <string>
#include <vector>

class reactant
{
private: 
	std::string _identifier;
	int _quantity;

public:
	reactant() = default;
	reactant(std::string identifier, int initial_quantity) : _identifier(identifier), _quantity(initial_quantity) {}

	friend std::vector<reactant> operator+(std::vector<reactant> const& lhs, std::vector<reactant> const& rhs) {
		std::vector<reactant> t;
		t.push_back(rhs.front());
		t.push_back(lhs.front());
		return t;
	};

	// LHS : Input, RHS : Output of '>>='
	friend std::vector<std::vector<reactant>> operator>>=(std::vector<reactant> input, std::vector<reactant> const& output) {
		std::vector<std::vector<reactant>> t;
		t.push_back(input);
		t.push_back(output);
		return t;
	}

	std::string getIdentifier() const {
		return _identifier;
	}
	int getQuanitity() const {
		return _quantity;
	}
};

