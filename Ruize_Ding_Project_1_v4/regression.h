#ifndef REFERENCE_H
#define REFERENCE_H

#include <vector>

class Regression {
private:
	double b0, b1;
	std::vector<double> ynew;
public:
	std::vector<std::vector<double>> data;
	std::vector<double> xnew;
	void train();
	void predict();
	void cout();
	void read_data();
	void read_train();
	void output();

	int plot1();
	int plot2();
};

#endif