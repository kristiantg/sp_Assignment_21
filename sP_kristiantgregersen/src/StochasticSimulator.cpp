#include "StochasticSimulator.h"
#include "SystemStateMonitor.h"

void StochasticSimulator::doMultithreadedStochaticSimulation(double& T, vector<reactant> state, vector<rule>& _rules, int& example, std::string& path, int& numberOfThreads)
{
	vector<std::thread> threads;
	for (auto i = 0; i < numberOfThreads; i++)
	{
		threads.push_back(std::thread([&]() {doStochaticSimulation(T, state, _rules, example, path);}));
	}

	for (auto& thread : threads) {
		thread.join();
	}
}

void StochasticSimulator::doStochaticSimulation(double& T, vector<reactant> state, vector<rule>& _rules, int& example, std::string& path)
{
	SystemStateMonitor<string> systemStateMonitor = SystemStateMonitor<string>{ "A" };
	std::ofstream file;
	file.open(path);

	if (file.is_open()) {
		if (example == 2) {
			file << "S,E,I,H,R,time\n";
		}
		else {
			file << "A,C,R,time\n";
		}
	}

	vector<double> delays;

	double t = 0;
	while (t <= T)
	{
		rule leastDelayRule;
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

		//monitorStateHelper
		auto test = getQuantity("H", state);
		systemStateMonitor.setCount(test);
		std::cout << systemStateMonitor.getMean() << std::endl;
		
		if (file.is_open()) {
			if (example == 2) {
				file << getQuantity("S", state) << "," << getQuantity("E", state) << "," << getQuantity("I", state) << "," << getQuantity("H", state) << "," << getQuantity("R", state) << "," << t << "\n";
			}
			else {
				file << getQuantity("A", state) << "," << getQuantity("C", state) << "," << getQuantity("R", state) << "," << t << "\n";
			}
		}
		//std::cout << "Time: " << t << "    A: " << getQuantity("A", state) << "    C: " << getQuantity("R", state) << "     R: " << getQuantity("R", state) << std::endl;
	}
	file.close();
}

bool StochasticSimulator::hasEnoughQuantities(vector<reactant>& input, vector<reactant>& state)
{
	bool isEnoughQuanity = true;
	for (auto& ruleInput : input) {
		if (ruleInput.getQuanitity() > getQuantity(ruleInput.getIdentifier(), state)) {
			isEnoughQuanity = false;
		}
	}
	return isEnoughQuanity;
}

void StochasticSimulator::changeQuantity(string reactantId, vector<reactant>& state, int ruleQuantity)
{
	for (auto& reactorState : state) {
		bool isSameReactant = reactorState.getIdentifier() == reactantId;

		if (isSameReactant) {
			reactorState.setQuantity(reactorState.getQuanitity() + ruleQuantity);
		}
	}
}

int StochasticSimulator::getQuantity(string reactantId, vector<reactant>& state)
{
	for (auto& reactorState : state) {
		bool isSameReactant = reactorState.getIdentifier() == reactantId;

		if (isSameReactant) {
			return reactorState.getQuanitity();
		}
	}
	return 0;
}
