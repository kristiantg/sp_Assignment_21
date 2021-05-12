#pragma once
#include<string>

template <class T>
class SystemStateMonitor
{
private:
	T stateToMonitorIdentifier;
	int count = 0;
	double dataPoints = 0;

public:
	SystemStateMonitor(std::string _stateToMonitorIdentifier) : stateToMonitorIdentifier(_stateToMonitorIdentifier) {}

	void setCount(int addedCount) {
		dataPoints++;
		count += addedCount;
	}

	double getMean() {
		if (dataPoints == 0)
			return 0;
		return count / dataPoints;
	}
};

