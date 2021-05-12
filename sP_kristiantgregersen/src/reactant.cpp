#include "reactant.h"

std::string reactant::getIdentifier() const {
	return _identifier;
};

int reactant::getQuanitity() const {
	return _quantity;
};

void reactant::setQuantity(int quantity) {
	_quantity = quantity;
};