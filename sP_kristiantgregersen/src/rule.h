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

	std::vector<reactant> const getOutput();
	std::vector<reactant>& getCatalysts();
	std::vector<reactant>& getInput();
	double& getTime();
	double getDelay(int quantity, double time);
};

