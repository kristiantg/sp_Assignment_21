#pragma once
#include <vector>
#include <string>
#include <exception>
#include <iostream>

// Custom exception. Thrown if element is not found.
struct ElementNotFoundException : public std::exception {
	const char* message() const throw () {
		return "Element not found.";
	}
};

// Symbol-table. Require for the user of the library to define a class with a method getIdentifier() to look up objects.
template <class T>
class SymbolTable
{
	std::vector<T> table;
public:
	SymbolTable(std::vector<T> _table) : table(_table) {}
	SymbolTable() = delete;

	// Insert into table.
	void insertIntoTable(T insert) {
		try {
			table.push_back(insert);
		}
		catch (ElementNotFoundException& e) {
			std::cout << e.message() << std::endl;
		}
	}

	// Delete from table. Throws exception if not found.
	void deleteFromTable(std::string lookup) {
		bool found = false;
		try {
			for (auto i = 0; i < table.size(); i++)
			{
				if (table.at(i).getIdentifier() == lookup) {
					table.erase(table.begin() + i);
					found = true;
					break;
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

	// Looks for element with a look-up key. Throws exception if not found.
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

