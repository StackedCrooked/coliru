#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


/**
 * Function that returns true if the 3 element powerset sum is equal to prot carb and fats
 */
bool PowerSet(std::vector<std::vector<int>> set, int set_size, int prot, int carb, int fats)
{
    const unsigned int powSetSize = std::pow(2, set_size);

	std::vector<std::vector<int>> options;
	for (unsigned counter = 0; counter < powSetSize; counter++) {
		int sum1 = 0;
		int sum2 = 0;
		int sum3 = 0;

		for (int j = 0; j < set_size; j++) {
			if (counter & (1 << j)) {
				sum1 += set[j][0];
				sum2 += set[j][1];
				sum3 += set[j][2];
			}
		}

		if (sum1 == prot && sum2 == carb && sum3 == fats) {
			return true;
		}
	}
	return false;
}



int main() {
	// Read the input into the text vector
	std::ifstream inputFile("input.txt");
	std::vector<std::string> text;
	std::copy(std::istream_iterator<std::string>(inputFile),
		std::istream_iterator<std::string>(),
		std::back_inserter(text));

	// Now we no longer need the first number so discard it
	text.erase(std::begin(text));

	// Open the output file
	std::ofstream output("output.txt");
	if (!output.is_open()) {
		std::cout << "Error opening file!" << std::endl;
		return -1;
	}

	int caseIndex = 1;
	// For each test case
	for (unsigned i = 0; i < text.size();) {
		std::cout << "Checking out: " << caseIndex << std::endl;

		// The first three lines are the amount of food he wants
		const int prot = std::stoi(text[i]);
		const int carb = std::stoi(text[i + 1]);
		const int fats = std::stoi(text[i + 2]);

		// The next line is the amount of food we can pick from
		const int amountFood = std::stoi(text[i + 3]);

		// Get all the food into vectors
		std::vector<std::vector<int>> foodOptions;
		for (int foods = 0; foods < amountFood * 3; foods += 3) {
			std::vector<int> currentNumberFood = {
				std::stoi(text[i + 4 + foods]),
				std::stoi(text[i + 5 + foods]),
				std::stoi(text[i + 6 + foods]),
			};

			if (currentNumberFood[0] > prot
				|| currentNumberFood[1] > carb
				|| currentNumberFood[2] > fats)
				continue;

			foodOptions.push_back(currentNumberFood);
		}

		bool maybe = PowerSet(foodOptions, foodOptions.size(), prot, carb, fats);

		output << "Case #" << caseIndex << ": " << (maybe ? "yes" : "no") << std::endl;
		caseIndex++;
		i += 4 + amountFood * 3;
	}

	output.close();
}