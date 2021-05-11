#pragma once
#include <list>
#include <string>
#include <vector>
#include <random>

using std::string;
using std::vector;
class reactant
{
private: 
	string _identifier;
	int _quantity;

public:
	reactant() = default;
	reactant(string identifier, int initial_quantity) : _identifier(identifier), _quantity(initial_quantity) {}

	friend vector<reactant> operator+(vector<reactant> lhs, vector<reactant> rhs) {
		vector<reactant> reactant;
		reactant.push_back(rhs.front());
		reactant.push_back(lhs.front());
		return reactant;
	};

	// LHS : Input 
	// RHS : Output of '>>='
	friend vector<vector<reactant>> operator>>=(vector<reactant> input, vector<reactant> const output) {
		vector<vector<reactant>> reactant;
		reactant.push_back(input);
		reactant.push_back(output);
		return reactant;
	}

	std::string getIdentifier() const {
		return _identifier;
	}

	int getQuanitity() const {
		return _quantity;
	}

	void setQuantity(int quantity)  {
		_quantity = quantity;
	}
};

