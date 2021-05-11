#pragma once
#include <vector>
#include "reactant.h"
#include <random>
#include <chrono>
class rule
{
private:
	std::vector<reactant> input_reactants;
	std::vector<reactant> output_reactants;
	std::vector<reactant> catalysts;
	double time;

public:
	rule() = default;
	rule(std::vector<reactant> input, std::vector<reactant> output, double _time) : input_reactants(input), output_reactants(output), time(_time) {}
	rule(std::vector<reactant> input, std::vector<reactant> output, std::vector<reactant> _catalysts, double _time) : input_reactants(input), output_reactants(output), catalysts(_catalysts), time(_time) {}

	std::vector<reactant> const getOutput() {
		return output_reactants;
	};

	std::vector<reactant>& getCatalysts() {
		return catalysts;
	};

	std::vector<reactant>& getInput() {
		return input_reactants;
	};

	double getTime()& {
		return time;
	};

	double getDelay(int quantity, double time) {
		std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
		double delay = quantity * time;

		if (delay == 0.0) {
			return std::numeric_limits<double>::infinity();
		};

		std::exponential_distribution<double> distribution(delay);
		return distribution(generator);
	};
};

