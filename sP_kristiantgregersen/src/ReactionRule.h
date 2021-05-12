#pragma once
#include <vector>
#include "reactant.h"
#include <random>
#include <chrono>
class ReactionRule
{
private:
	std::vector<Reactant> input_reactants;
	std::vector<Reactant> output_reactants;
	std::vector<Reactant> catalysts;
	double time;

public:
	ReactionRule() = default;
	ReactionRule(std::vector<Reactant> input, std::vector<Reactant> output, double _time) : input_reactants(input), output_reactants(output), time(_time) {}
	ReactionRule(std::vector<Reactant> input, std::vector<Reactant> output, std::vector<Reactant> _catalysts, double _time) : input_reactants(input), output_reactants(output), catalysts(_catalysts), time(_time) {}

	std::vector<Reactant> const getOutput();
	std::vector<Reactant>& getCatalysts();
	std::vector<Reactant>& getInput();
	double& getTime();
	double getDelay(int& quantity, double& time);
};

