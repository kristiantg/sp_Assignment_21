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
	StochasticSimulator(string reactantId, string path, string headers, int flag, bool toMonitor) : reactantIdToMonitor(reactantId), filePath(path), fileHeaders(headers), exampleFlag(flag), willMonitorSystem(toMonitor) {}
	StochasticSimulator(string path, string headers, int flag, bool toMonitor) : filePath(path), fileHeaders(headers), exampleFlag(flag), willMonitorSystem(toMonitor){}

	void doMultithreadedStochaticSimulation(double& T, vector<Reactant> state, vector<ReactionRule>& _rules, int& numberOfThreads);
	void doStochaticSimulation(double& T, vector<Reactant> state, vector<ReactionRule>& _rules);
	void printTrajectory(vector<Reactant>& state, double& t, std::ofstream& file);

	string getFilePath();
	string getFileHeaders();
	string getReactantToMonitor();
	int getExampleFlag();
	bool getToMonitor();

private:
	string reactantIdToMonitor;
	string filePath;
	string fileHeaders;
	int exampleFlag;
	bool willMonitorSystem = false;
	
	bool hasEnoughQuantities(vector<Reactant>& input, vector<Reactant>& state);
	void changeQuantity(string reactantId, vector<Reactant>& state, int ruleQuantity);
	int getQuantity(string reactantId, vector<Reactant>& state);
};

