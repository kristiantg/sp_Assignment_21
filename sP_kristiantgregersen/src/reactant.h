#pragma once
#include <list>
#include <string>
#include <vector>
#include <random>

using std::string;
using std::vector;
class Reactant
{
private: 
	string _identifier;
	int _quantity;

public:
	Reactant() = default;
	Reactant(string identifier, int quantity) : _identifier(identifier), _quantity(quantity) {}

	friend vector<Reactant> operator+(vector<Reactant> lhs, vector<Reactant> rhs) {
		vector<Reactant> reactant;
		reactant.push_back(rhs.front());
		reactant.push_back(lhs.front());
		return reactant;
	};

	friend vector<vector<Reactant>> operator>>=(vector<Reactant> input, vector<Reactant> output) {
		vector<vector<Reactant>> reactant;
		reactant.push_back(input);
		reactant.push_back(output);
		return reactant;
	}

	std::string getIdentifier() const;
	int getQuanitity() const;

	void setQuantity(int quantity);
};

