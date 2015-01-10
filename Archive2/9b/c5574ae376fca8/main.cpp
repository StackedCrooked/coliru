#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>


using Format = std::tuple<int, int, int>;


/**
* Function that returns true if the N element powerset sum is equal to the Tuple input
*/
auto PowerSet(const std::vector<Format>& set, const Format& needs) {
    const unsigned setSize = set.size();
    const unsigned powSetSize = std::pow(2, setSize);

	for (unsigned counter = 0; counter < powSetSize; counter++) {
		int sum1 = 0;
		int sum2 = 0;
		int sum3 = 0;

		for (unsigned j = 0; j < setSize; j++) {
			if (counter & (1 << j)) {
				sum1 += std::get<0>(set[j]);
				sum2 += std::get<1>(set[j]);
				sum3 += std::get<2>(set[j]);
			}
		}

		if (std::tie(sum1, sum2, sum3) == needs) {
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

	if (text.size() == 0) {
		std::cout << "Input file could not be read";
		return -1;
	}

	// Now we no longer need the first number so discard it
	text.erase(std::begin(text));

	// Open the output file
	std::ofstream output("output.txt");
	if (!output.is_open()) {
		std::cout << "Error opening output file!" << std::endl;
		return -1;
	}

	int caseIndex = 1;
	// For each test case
	for (unsigned i = 0; i < text.size();) {
		// The first three lines are the amount of food he wants
		const auto needs = Format(
			std::stoi(text[i]), std::stoi(text[i + 1]), std::stoi(text[i + 2])
		);

		// The next line is the amount of food we can pick from
		const int amountFood = std::stoi(text[i + 3]);

		// Get all the food into vectors
		std::vector<Format> foodOptions;
		for (int foods = 0; foods < amountFood * 3; foods += 3) {
			const auto currentNumberFood = Format(
				std::stoi(text[i + 4 + foods]),
				std::stoi(text[i + 5 + foods]),
				std::stoi(text[i + 6 + foods])
			);

			if (currentNumberFood > needs) {
				continue;
			}

			foodOptions.push_back(currentNumberFood);
		}

		if (PowerSet(foodOptions, needs)) {
			output << "Case #" << caseIndex << ": yes" << std::endl;
		}
		else {
			output << "Case #" << caseIndex << ": no" << std::endl;
		}

		caseIndex++;
		i += 4 + amountFood * 3;
	}

	output.close();
}