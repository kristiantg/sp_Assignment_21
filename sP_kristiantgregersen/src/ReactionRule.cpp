#include "ReactionRule.h"
#include <iostream>

std::vector<Reactant> const ReactionRule::getOutput()
{
	return output_reactants;
};

std::vector<Reactant>& ReactionRule::getCatalysts()
{
	return catalysts;
};

std::vector<Reactant>& ReactionRule::getInput()
{
	return input_reactants;
};

double& ReactionRule::getTime()
{
	return time;
};

// Computes the delay for the stochastic simulator. Receives time (decay) and the amount of reactants.
double ReactionRule::getDelay(int& quantity, double& time)
{
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	double delay = quantity * time;

	if (delay == 0.0) {
		return std::numeric_limits<double>::infinity();
	};

	std::exponential_distribution<double> distribution(delay);
	return distribution(generator);
};
