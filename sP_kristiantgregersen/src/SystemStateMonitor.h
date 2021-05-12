#pragma once
#include<string>

// Keeps track of max, number of data-points and the average quanties over time.
template <class T>
class SystemStateMonitor
{
private:
	T stateToMonitorIdentifier;
	int count = 0;
	double dataPoints = 0;
	int max = 0;

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

	void setMax(double addedCount) {
		if (max < addedCount) {
			max = addedCount;
		}
	}

	double getMax() {
		return max;
	}
};

