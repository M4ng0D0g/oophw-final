#pragma once 

#include <string>

class Score {
private:
	long long realInt_ = 0;
	double realFloat_ = 0.;
	bool realValid_ = true;

	long long imaginary_ = 0;
	double imaginaryFloat_ = 0.;
	bool imaginaryValid_ = true;

public:
	// void addReal(long long);
	// void removeReal(long long);
	// void addImaginary(long long);
	// void removeImaginary(long long);

	std::string toStr() const;
};