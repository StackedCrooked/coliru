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

food operator+(const food & lhs, const food & rhs) {
	return std::make_tuple(std::get<0>(lhs) + std::get<0>(rhs), std::get<1>(lhs) + std::get<1>(rhs), std::get<2>(lhs) + std::get<2>(rhs));
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
bool depthFirst(const food & totalFood, const food & accum, const std::vector<food> & foods) {
	if (accum >= totalFood) {
//		if (accum == totalFood) {
//			std::cout << foods;
//		}
		return accum == totalFood;
	}
	for (std::size_t i = 0; i < foods.size(); ++i) {
		auto newFood = foods;
		const auto newAccum = accum + foods[i];
		newFood.erase(std::begin(newFood) + i);
		if (depthFirst(totalFood, newAccum, newFood)) {
			return true;
		}
	}
	return false;
}

bool breadthFirst(const food & totalFood, const food & accum, const std::vector<food> & foods) {

}

std::string test(std::ifstream & inFile) {
	int totalProtein, totalCarbo, totalFat;
	inFile >> totalProtein >> totalCarbo >> totalFat;
	const food totalFood{totalProtein, totalCarbo, totalFat};
	int foodCount;
	inFile >> foodCount;
	std::vector<food> foods;
	int eraseCounter = 0;
	for (int i = 0; i < foodCount; ++i) {
		int protein, carbo, fat;
		inFile >> protein >> carbo >> fat;
		if (protein <= totalProtein && carbo <= totalCarbo && fat <= totalFat) {
			foods.emplace_back(protein, carbo, fat);
		} else {
			++eraseCounter;
		}
	}
	std::cout << "erased " << eraseCounter << std::endl;
	const food maxFood = std::accumulate(std::begin(foods), std::end(foods), food{0, 0, 0}, [](const food & accum, const food & add){
		return accum + add;
	});
	if (maxFood < totalFood) {
		return "no";
	}

	/*
	return depthFirst(totalFood, food{0, 0, 0}, foods) ? "yes" : "no";
	/*/
	do {
		food accum{0, 0, 0};
//		std::cout << foods << std::endl;
		for (auto && elem : foods) {
//			std::cout << accum << std::endl;
			if (accum == totalFood) {
				return "yes";
			}
			accum = accum + elem;
			if (accum == totalFood) {
				return "yes";
			}
		}
	} while (std::next_permutation(std::begin(foods), std::end(foods)));

	return "no";
	//*/
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
