#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <string>

#include "UnionFind.h"
#include "Algorithms.h"

int main(int argc, char* argv[])
{
    size_t numIterations = 20;
	std::vector<long long> shellSortDurations(numIterations, 0);
	std::vector<long long> stdSortDurations(numIterations, 0);

	for(size_t i = 0; i < numIterations; i++)
	{
		std::vector<char> benchstr(10000);
		std::random_device randomDev;
		std::for_each(std::begin(benchstr), std::end(benchstr), [&randomDev](char& c) { c = randomDev(); });

		std::vector<char> benchstr1(benchstr);
		std::chrono::high_resolution_clock::time_point start1 = std::chrono::high_resolution_clock::now();
		tt::algo::shellSort(std::begin(benchstr1), std::end(benchstr1), tt::algo::Sedgewick2Seq(), std::less<char>());
		std::chrono::high_resolution_clock::time_point end1 = std::chrono::high_resolution_clock::now();
		shellSortDurations[i] = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count();

		std::vector<char> benchstr2(benchstr);
		std::chrono::high_resolution_clock::time_point start2 = std::chrono::high_resolution_clock::now();
		std::sort(std::begin(benchstr2), std::end(benchstr2), std::less<char>());
		std::chrono::high_resolution_clock::time_point end2 = std::chrono::high_resolution_clock::now();
		stdSortDurations[i] = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count();
	}

	auto shellSortDurationSum = std::accumulate(shellSortDurations.begin(), shellSortDurations.end(), 0);
	auto stdSortDurationSum = std::accumulate(stdSortDurations.begin(), stdSortDurations.end(), 0);

	auto shellSortDurationAvg = shellSortDurationSum / numIterations;
	auto stdSortDurationAvg = stdSortDurationSum / numIterations;

	std::cout << "Shell sort took on avg: " << shellSortDurationAvg << "us.\n";
	std::cout << "Std sort took on avg:   " << stdSortDurationAvg << "us.\n";

	std::cin.get();
	return 0;
}