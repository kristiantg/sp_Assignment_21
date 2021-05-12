#pragma once
#include <string>
#include <vector>
#include "ReactionRule.h"
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

	void doMultithreadedStochaticSimulation(double& T, vector<Reactant> state, vector<ReactionRule>& _rules, int& example, string& path, int& numberOfThreads);
	void doStochaticSimulation(double& T, vector<Reactant> state, vector<ReactionRule>& _rules, int& example, string& path);
private:
	bool hasEnoughQuantities(vector<Reactant>& input, vector<Reactant>& state);
	void changeQuantity(string reactantId, vector<Reactant>& state, int ruleQuantity);
	int getQuantity(string reactantId, vector<Reactant>& state);
};

