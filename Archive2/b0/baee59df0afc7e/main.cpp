#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>

using food = std::tuple<int, int, int>;

std::ostream& operator<<(std::ostream & out, const food & elem) {
    return out << std::get<0>(elem) << ' ' << std::get<1>(elem) << ' ' << std::get<2>(elem);
}

template<typename T>
std::ostream& operator<<(std::ostream & out, std::vector<T> vec) {
	out << '{';
	for (auto && elem : vec) {
		out << '[' << elem << ']';
	}
	return out << '}';
}

food & operator+(food & lhs, const food & rhs) {
	std::get<0>(lhs) += std::get<0>(rhs);
	std::get<1>(lhs) += std::get<1>(rhs);
	std::get<2>(lhs) += std::get<2>(rhs);
	return lhs;
}

/*
bool operator<(const food & lhs, const food & rhs) {
	return std::get<0>(lhs) < std::get<0>(rhs)
		|| (std::get<0>(lhs) == std::get<0>(rhs)
			&& (std::get<1>(lhs) < std::get<1>(rhs)
			|| (std::get<1>(lhs) == std::get<1>(rhs)
				&& std::get<2>(lhs) < std::get<2>(rhs))));
}
*/
std::string test(std::ifstream & inFile) {
	int totalProtein, totalCarbo, totalFat;
	inFile >> totalProtein >> totalCarbo >> totalFat;
	int foodCount;
	inFile >> foodCount;
	std::vector<food> foods(foodCount);
	for (int i = 0; i < foodCount; ++i) {
		int protein, carbo, fat;
		inFile >> protein >> carbo >> fat;
		foods[i] = std::make_tuple(protein, carbo, fat);
	}
	const food total{totalProtein, totalCarbo, totalFat};
	do {
		food accum{0, 0, 0};
//		std::cout << foods << std::endl;
		for (auto && elem : foods) {
//			std::cout << accum << std::endl;
			if (total == accum) {
				return "yes";
			}
			accum = accum + elem;
			if (total == accum) {
				return "yes";
			}
		}
	} while (std::next_permutation(std::begin(foods), std::end(foods)));

	return "no";
}

int main() {
	std::ifstream inFile("new_years_resolution.txt");
	inFile.exceptions(std::ifstream::failbit);

	std::string line;
	std::getline(inFile, line);
	std::size_t testCaseCount{std::stoull(line)};

	for (std::size_t testCase = 1; testCase <= testCaseCount; ++testCase) {
		std::cout << "Case #" << testCase << ": " << test(inFile) << std::endl;
	}
}
