#include "StochasticSimulator.h"
#include "SystemStateMonitor.h"

void StochasticSimulator::doMultithreadedStochaticSimulation(double& T, vector<Reactant> state, vector<ReactionRule>& _rules, int& numberOfThreads)
{
	vector<std::thread> threads;
	for (auto i = 0; i < numberOfThreads; i++)
	{
		threads.push_back(std::thread([&]() {doStochaticSimulation(T, state, _rules);}));
	}

	for (auto& thread : threads) {
		thread.join();
	}
}

void StochasticSimulator::doStochaticSimulation(double& T, vector<Reactant> state, vector<ReactionRule>& _rules)
{
	SystemStateMonitor<string> systemStateMonitor = SystemStateMonitor<string>{ getReactantToMonitor() };
	vector<double> delays;
	std::ofstream file;

	file.open(getFilePath());
	if (file.is_open()) {
		file << getFileHeaders();
	}

	double t = 0;
	while (t <= T)
	{
		ReactionRule leastDelayRule;
		double leastDelay = 100000;

		for (auto& rule : _rules) {
			int totalQuantity = 1;
			for (auto& input : rule.getInput()) {
				totalQuantity *= getQuantity(input.getIdentifier(), state);
			};

			for (auto& catalyst : rule.getCatalysts()) {
				totalQuantity *= getQuantity(catalyst.getIdentifier(), state);
			};

			double currentDelay = rule.getDelay(totalQuantity, rule.getTime());
			if (currentDelay < leastDelay) {
				leastDelay = currentDelay;
				leastDelayRule = rule;
			}
		}
		t += leastDelay;

		bool isEnoughQuanity = true;

		isEnoughQuanity = hasEnoughQuantities(leastDelayRule.getInput(), state);
		isEnoughQuanity &= hasEnoughQuantities(leastDelayRule.getCatalysts(), state);

		if (isEnoughQuanity) {
			for (auto& ruleInput : leastDelayRule.getInput()) {
				changeQuantity(ruleInput.getIdentifier(), state, -ruleInput.getQuanitity());
			}
			for (auto& ruleOutput : leastDelayRule.getOutput()) {
				changeQuantity(ruleOutput.getIdentifier(), state, ruleOutput.getQuanitity());
			}
		}

		if (getToMonitor()) {
			systemStateMonitor.setCount(getQuantity(getReactantToMonitor(), state));
			std::cout << systemStateMonitor.getMean() << std::endl;
			std::cout << systemStateMonitor.getMean() << std::endl;
		}

		printTrajectory(state, t, file);
	}
	file.close();
}

void StochasticSimulator::printTrajectory(vector<Reactant>& state, double& t, std::ofstream& file) {
	if (file.is_open()) {
		if (getExampleFlag() == 2) {
			file << getQuantity("S", state) << "," << getQuantity("E", state) << "," << getQuantity("I", state) << "," << getQuantity("H", state) << "," << getQuantity("R", state) << "," << t << "\n";
		}
		else {
			file << getQuantity("A", state) << "," << getQuantity("C", state) << "," << getQuantity("R", state) << "," << t << "\n";
		}
	}
}

bool StochasticSimulator::hasEnoughQuantities(vector<Reactant>& input, vector<Reactant>& state)
{
	bool isEnoughQuanity = true;
	for (auto& ruleInput : input) {
		if (ruleInput.getQuanitity() > getQuantity(ruleInput.getIdentifier(), state)) {
			isEnoughQuanity = false;
		}
	}
	return isEnoughQuanity;
}

void StochasticSimulator::changeQuantity(string reactantId, vector<Reactant>& state, int ruleQuantity)
{
	for (auto& reactorState : state) {
		bool isSameReactant = reactorState.getIdentifier() == reactantId;

		if (isSameReactant) {
			reactorState.setQuantity(reactorState.getQuanitity() + ruleQuantity);
		}
	}
}

int StochasticSimulator::getQuantity(string reactantId, vector<Reactant>& state)
{
	for (auto& reactorState : state) {
		bool isSameReactant = reactorState.getIdentifier() == reactantId;

		if (isSameReactant) {
			return reactorState.getQuanitity();
		}
	}
	return 0;
}

string StochasticSimulator::getFilePath()
{
	return filePath;
}

string StochasticSimulator::getFileHeaders()
{
	return fileHeaders;
}

string StochasticSimulator::getReactantToMonitor()
{
	return reactantIdToMonitor;
}

int StochasticSimulator::getExampleFlag()
{
	return exampleFlag;
}

bool StochasticSimulator::getToMonitor()
{
	return willMonitorSystem;
}
