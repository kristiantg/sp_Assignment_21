#include "reactant.h"

std::string Reactant::getIdentifier() const {
	return _identifier;
};

int Reactant::getQuanitity() const {
	return _quantity;
};

void Reactant::setQuantity(int quantity) {
	_quantity = quantity;
};