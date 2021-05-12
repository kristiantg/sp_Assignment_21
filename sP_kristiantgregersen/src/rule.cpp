#include "rule.h"
#include <iostream>

std::vector<reactant> const rule::getOutput()
{
	return output_reactants;
};

std::vector<reactant>& rule::getCatalysts()
{
	return catalysts;
};

std::vector<reactant>& rule::getInput()
{
	return input_reactants;
};

double& rule::getTime()
{
	return time;
};

double rule::getDelay(int& quantity, double& time)
{
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	double delay = quantity * time;

	if (delay == 0.0) {
		return std::numeric_limits<double>::infinity();
	};

	std::exponential_distribution<double> distribution(delay);
	return distribution(generator);
};
