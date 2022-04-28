#include "regression.h"

int main() {
	Regression part1;
	part1.data = { {5, 43.1}, {7.1, 32.1}, {34.5, 40.3}, {13, 39.3}, {1.5, 47.7} };
	part1.xnew = { 1, 2, 3, 4, 5 };
	part1.train();
	part1.predict();
	part1.cout();
	part1.plot1();

	Regression part2;
	part2.read_data();
	part2.train();
	part2.read_train();
	part2.predict();
	part2.output();
	part2.plot2();
}