#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


/**
 * Function that converts a number to a vector of digits (int)
 */
template <typename T>
inline std::vector<int> AsDigitVector(const T& number) {
    static_assert(std::is_integral<T>::value,
		"Need a number for this function");
	
	int copy = number;
	std::vector<int> digits;

	while (copy) {
		digits.push_back(copy % 10);
		copy /= 10;
	}
	// This order is reversed
	std::reverse(std::begin(digits), std::end(digits));
	return std::move(digits);
}


/**
 * Function that lines up for a correct output
 */
std::string PrintResult(const int& index, const std::vector<int>& actualHigh, const std::vector<int>& digitVector)
{
	std::string result = "Case #" + std::to_string(index) + ": ";

	// Low is fixed so let's write it to the file 
	for (const auto& num : digitVector) {
		result += std::to_string(num);
	}

	// Put a space between them
	result += " ";

	// High is fixed so let's write it to the file
	for (const auto& num : actualHigh) {
		result += std::to_string(num);
	}

	result += "\n";
	return result;
}


template <bool T>
struct Reverse { static std::vector<int> FixSort(const std::vector<int>& original); };


template <>
std::vector<int> Reverse<true>::FixSort(const std::vector<int>& original) {
	std::vector<int> returnVec = original;

	// Sort the vectors to get the optimal conditions
	std::sort(std::rbegin(returnVec), std::rend(returnVec));
	
	// Now we remove all zero's because they are pointless
	returnVec.erase(std::remove(std::begin(returnVec), std::end(returnVec), 0), std::end(returnVec));
	return returnVec;
}


template <>
std::vector<int> Reverse<false>::FixSort(const std::vector<int>& original) {
	std::vector<int> returnVec = original;

	// Sort the vectors to get the optimal conditions
	std::sort(std::begin(returnVec), std::end(returnVec));

	// Now we remove all zero's because they are pointless
	returnVec.erase(std::remove(std::begin(returnVec), std::end(returnVec), 0), std::end(returnVec));
	return returnVec;
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

	// This keeps track of the case number
	int index = 0;

	// Open the output file
	std::ofstream output("output.txt");
	if (!output.is_open()) {
		std::cout << "Error opening file!" << std::endl;
		return -1;
	}

	// For each test case
	for (const auto& current : text) {
		// Increment the index (we start at 1)
		index++;
		
		// Convert the string to a number
		const int number = std::stoi(current);

		// If it is small enough just print it without reordering
		if (number <= 11) {
			output << "Case #" << index << ": " << number << " " << number << std::endl;
			continue;
		}

		// It is larger so we want to sort it to find out the optimal sequence
		std::vector<int> digitVector = AsDigitVector<int>(number);
		std::vector<int> Hbound = Reverse<true>::FixSort(digitVector);
		std::vector<int> Lbound = Reverse<false>::FixSort(digitVector);

		std::vector<int> actualHigh = digitVector;
		std::vector<int> actualLow	= digitVector;

		// Actually delete these
		actualLow.erase(std::remove(std::begin(actualLow), std::end(actualLow), 0), std::end(actualLow));

		// Let's fix the Lower
		for (unsigned i = 0; i < Lbound.size(); i++) {
			// If the digit is in optimal condition just skip to the next one
			if (Lbound[i] == actualLow[i]) {
				continue;
			}

			// Reverse search actualHigh for the Hbound digit we like
			for (int j = digitVector.size() - 1; j >= 0; j--) {
				if (digitVector[j] == Lbound[i]) {
					// Find the highest occurence of actualLow[i]
					for (unsigned k = 0; k < digitVector.size(); k++) {
						if (digitVector[k] == actualLow[i]) {
							digitVector[k] = Lbound[i];
							break;
						}
					}
					// Okay so now we just swap them
					digitVector[j] = actualLow[i];
					break;
				}
			}
			break;
		}

		// Let's fix the Higher
		for (unsigned i = 0; i < Hbound.size(); i++) {
			// If the digit is in optimal condition just skip to the next one
			if (Hbound[i] == actualHigh[i]) {
				continue;
			}

			// Reverse search actualHigh for the Hbound digit we like
			for (int j = actualHigh.size() - 1; j >= 0; j--) {
				if (actualHigh[j] == Hbound[i]) {
					// Okay so now we just swap them
					actualHigh[j] = actualHigh[i];
					actualHigh[i] = Hbound[i];
					break;
				}
			}
			break;
		}

		output << PrintResult(index, actualHigh, digitVector);
	}

	output.close();
}