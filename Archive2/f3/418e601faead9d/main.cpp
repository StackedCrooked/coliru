// TailRecursionOptimization.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <algorithm>
#include <cmath>

std::string ReverseString(std::string str)
{
    if (str.empty())
	{
		return str;
	}
	else
	{
		return ReverseString(str.substr(1)) + str[0];
	}
}

std::string ReverseString2(std::string rest, std::string reversed = "")
{
	if (rest.empty())
	{
		return reversed;
	}
	else
	{
		return ReverseString2(rest.substr(1), rest[0] + reversed);
	}
}

void Verify(const std::string &msg, std::function<std::string()> func, const std::string &expectedResult)
{
	if (expectedResult != func())
	{
		throw new std::runtime_error("Unexpected result for " + msg);
	}
}

void Measure(const std::string &msg, size_t numberRepetitions, std::function<std::string()> func)
{
	auto begin = std::chrono::steady_clock::now();

	for (size_t index = 0 ; index < numberRepetitions; ++index)
	{
		std::string result = func();
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	long long ms = diff.count();

	std::cout 
		<< msg 
		<< " took " 
		<< std::setfill('0')
		<< std::setw(2)
		<< static_cast<int>(std::floor(ms/3600000))
		<< ":" 
		<< std::setw(2)
		<< std::floor(ms/60000)
		<< ":" 
		<< std::setw(2)
		<< ms/1000
		<< "." 
		<< ms % 1000
		<< std::endl;
}

int main(int argc, char* argv[])
{
	const std::string input = "ABCDEFGHIJKLMN";
	const int numberOfIterations = 10000000;
	
	std::string result = input;
	std::reverse(result.begin(), result.end());

	Verify("ReverseString", [input]() { return ReverseString(input); }, result);
	Verify("ReverseString2", [input]() { return ReverseString(input); }, result);

	Measure("ReverseString", numberOfIterations, [input]() { return ReverseString(input); });
	Measure("ReverseString2", numberOfIterations, [input]() { return ReverseString(input); });
	return 0;
}

