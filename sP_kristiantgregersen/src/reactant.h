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
	reactant(string identifier, int quantity) : _identifier(identifier), _quantity(quantity) {}

	friend vector<reactant> operator+(vector<reactant> lhs, vector<reactant> rhs) {
		vector<reactant> reactant;
		reactant.push_back(rhs.front());
		reactant.push_back(lhs.front());
		return reactant;
	};

	friend vector<vector<reactant>> operator>>=(vector<reactant> input, vector<reactant> const output) {
		vector<vector<reactant>> reactant;
		reactant.push_back(input);
		reactant.push_back(output);
		return reactant;
	}

	std::string getIdentifier() const;
	int getQuanitity() const;

	void setQuantity(int quantity);
};

