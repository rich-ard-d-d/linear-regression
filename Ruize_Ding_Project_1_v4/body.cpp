#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "pbPlots.hpp"
#include "supportLib.hpp"
#include "regression.h"

void Regression::train() {
	double xtot = 0, ytot = 0, xbar, ybar, numerator = 0, denominator = 0;
	for (int i = 0; i < data.size(); i++) {
		xtot += data[i][0];
		ytot += data[i][1];
	}
	xbar = xtot / data.size();
	ybar = ytot / data.size();
	for (int i = 0; i < data.size(); i++) {
		numerator += (data[i][0] - xbar) * (data[i][1] - ybar);
		denominator += pow((data[i][0] - xbar), 2);
	}
	b1 = numerator / denominator;
	b0 = ybar - b1 * xbar;
}

void Regression::predict() {
	for (int i = 0; i < xnew.size(); i++) {
		ynew.push_back(b0 + b1 * xnew[i]);
	}
}

void Regression::cout() {
	std::cout << "B1 (slope): " << b1 << "\n";
	std::cout << "B0 (y-intercept): " << b0 << "\n";
	std::cout << "Regression formula: y = " << b0 << " + " << b1 << "x \n";
	for (int i = 0; i < xnew.size(); i++) {
		std::cout << "(" << xnew[i] << "," << ynew[i] << ")\n";
	}
}

void Regression::read_data() {
	std::ifstream read("data.csv");
	if (read.is_open()) {
		std::string line;
		std::vector<double> tempVector;
		while (getline(read, line)) {
			double x, y;
			std::string tempString;
			std::stringstream inputString(line);
			getline(inputString, tempString, ',');
			x = std::stod(tempString.c_str());
			getline(inputString, tempString);
			y = std::stod(tempString.c_str());
			tempVector.push_back(x);
			tempVector.push_back(y);
			data.push_back(tempVector);
			tempVector.clear();
		}
	}
	read.close();
}

void Regression::read_train() {
	std::ifstream read("test.csv");
	if (read.is_open()) {
		std::string line;
		while (getline(read, line)) {
			double x;
			x = std::stod(line.c_str());
			xnew.push_back(x);
		}
	}
	read.close();
}

void Regression::output() {
	std::ofstream output("Output.txt");
	if (output.is_open()) {
		output << "B1 (slope): " << b1 << "\n";
		output << "B0 (y-intercept): " << b0 << "\n";
		output << "Regression formula: y = " << b0 << " + " << b1 << "x \n";
		for (int i = 0; i < xnew.size(); i++) {
			output << "(" << xnew[i] << "," << ynew[i] << ")\n";
		}
	}
	else std::cout << "Output file does not open";
	output.close();
}

int Regression::plot1() {
	bool success;
	StringReference* errorMessage = new StringReference();
	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

	success = DrawScatterPlot(imageReference, 600, 400, &xnew, &ynew, errorMessage);

	if (success) {
		std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
		WriteToFile(pngdata, "part_1.png");
		DeleteImage(imageReference->image);
	}
	else {
		std::cerr << "Error: ";
		for (wchar_t c : *errorMessage->string) {
			std::wcerr << c;
		}
		std::cerr << std::endl;
	}

	return success ? 0 : 1;
}

int Regression::plot2() {
	bool success;
	StringReference* errorMessage = new StringReference();
	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

	success = DrawScatterPlot(imageReference, 600, 400, &xnew, &ynew, errorMessage);

	if (success) {
		std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
		WriteToFile(pngdata, "part_2.png");
		DeleteImage(imageReference->image);
	}
	else {
		std::cerr << "Error: ";
		for (wchar_t c : *errorMessage->string) {
			std::wcerr << c;
		}
		std::cerr << std::endl;
	}

	return success ? 0 : 1;
}