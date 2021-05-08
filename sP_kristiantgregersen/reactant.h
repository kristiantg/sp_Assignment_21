#pragma once
#include <list>

class reactant
{
public:
	reactant operator+(const reactant& other) {
		return other;
	}

	reactant operator>>=(const reactant& other) {
		return other;
	}

	reactant operator>>=(std::list<reactant>& b) {
	}

};

