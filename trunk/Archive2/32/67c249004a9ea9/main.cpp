#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <random>
#include <exception>
#include <type_traits>
#include <boost/lexical_cast.hpp>

using namespace std;

// 1. A way to easily measure elapsed time -------------------
template<typename TimeT = std::chrono::milliseconds>
struct measure
{
    template<typename F>
	static typename TimeT::rep execution(F const &func)
	{
		auto start = std::chrono::system_clock::now();
		func();
		auto duration = std::chrono::duration_cast< TimeT>(
			std::chrono::system_clock::now() - start);
		return duration.count();
	}
};
// -----------------------------------------------------------

// 2. Define the convertion functions ========================
// A. Using boost::lexical_cast ------------------------------
template<typename Ret> 
Ret NumberFromString(string const &value) {
	return boost::lexical_cast<Ret>(value);
}

// B. Using c++11 stoi() -------------------------------------
int IntFromString(string const &value) { 
	return std::stoi(value);
}

// C. Using c++11 stof() -------------------------------------
float FloatFromString(string const &value) { 
	return std::stof(value);
}
// ===========================================================

// 3. A wrapper to measure the different executions ----------
template<typename T, typename F> long long 
MeasureExec(std::vector<string> const &v1, F const &func)
{
	return measure<>::execution([&]() {
		for (auto const &i : v1) {
			if (func(i) != NumberFromString<T>(i)) {
				throw std::runtime_error("FAIL");
			}
		}
	});
}
// -----------------------------------------------------------

// 4. Machinery to generate random numbers into a vector -----
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
FillVec(vector<T> &v)
{
	mt19937 e2(1);
	uniform_int_distribution<> dist(3, 1440);
	generate(v.begin(), v.end(), [&]() { return dist(e2); });
}

template<typename T>
typename std::enable_if<!std::is_integral<T>::value>::type
FillVec(vector<T> &v)
{
	mt19937 e2(1);
	uniform_real_distribution<> dist(-1440., 1440.);
	generate(v.begin(), v.end(), [&]() { return dist(e2); });
}

template<typename T>
void FillVec(vector<T> const &vec, vector<string> *result)
{
	result->resize(vec.size());
	for (size_t i = 0; i < vec.size(); i++)
		result->at(i) = boost::lexical_cast<string>(vec[i]);
}
// -----------------------------------------------------------

int main()
{
	std::vector<int> vi(991908);
	FillVec(vi);
	std::vector<float> vf(991908);
	FillVec(vf);

	std::vector<string> vsi, vsf;
	FillVec(vi, &vsi);
	FillVec(vf, &vsf);

	cout << "C++ 11 stof function .. " <<
		MeasureExec<float>(vsf, FloatFromString) << endl;
	cout << "Lexical cast method ... " <<
		MeasureExec<float>(vsf, NumberFromString<float>) << endl;

	cout << endl << endl;

	cout << "C++ 11 stoi function .. " <<
		MeasureExec<int>(vsi, IntFromString) << endl;
	cout << "Lexical cast method ... " <<
		MeasureExec<int>(vsi, NumberFromString<int>) << endl;

	return 0;
}