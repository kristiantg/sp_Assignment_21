#pragma once
#include <vector>
#include <string>
#include <exception>
#include <iostream>

struct ElementNotFoundException : public std::exception {
	const char* message() const throw () {
		return "Element not found.";
	}
};

template <class T>
class SymbolTable
{
	std::vector<T> table;
public:
	SymbolTable(std::vector<T> _table) : table(_table) {}

	void insertIntoTable(T insert) {
		try {
			table.push_back(insert);
		}
		catch (ElementNotFoundException& e) {
			std::cout << e.message() << std::endl;
		}
	}

	void deleteFromTable(T lookup) {
		bool found = false;
		try {
			for (auto& element : table) {
				if (element.getIdentifier() == lookup) {
					table.erase(element);
					found = true;
					break;
				}
				if (!found) {
					throw ElementNotFoundException();
				}
			}
		}
		catch (ElementNotFoundException& e) {
			std::cout << e.message() << std::endl;
		}
	}

	T lookupTable(std::string lookupKey) {
		bool found = false;
		try {
			for (auto& element : table) {
				if (element.getIdentifier() == lookupKey) {
					found = true;
					return element;
				}
			}
			if (!found) {
				throw ElementNotFoundException();
			}
		}
		catch (ElementNotFoundException& e) {
			std::cout << e.message() << std::endl;
		}
	}
};

