#pragma once
#include <string>
#include <vector>
#include "rule.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <future>

using std::string;
using std::vector;
class StochasticSimulator
{
public:
	StochasticSimulator() = default;

	void doMultithreadedStochaticSimulation(double T, vector<reactant> state, vector<rule> _rules, int example);
	void doStochaticSimulation(double T, vector<reactant> state, vector<rule> _rules, int example);
private:
	bool hasEnoughQuantities(vector<reactant>& input, vector<reactant>& state);
	void changeQuantity(string reactantId, vector<reactant>& state, int ruleQuantity);
	int getQuantity(string reactantId, vector<reactant>& state);
};

