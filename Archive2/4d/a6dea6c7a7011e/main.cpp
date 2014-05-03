#include <boost/spirit/include/karma.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <random>
#include <boost/lexical_cast.hpp>

using namespace std;

// A way to easily measure elapsed time ---------------------
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

// Define functions that use 3 different ways that -----------
// c++ has to convert integrals to strings -------------------
template<typename T> // 2. Using boost::lexical_cast
string StringFromIntegral_LC(T const &value) {
    return boost::lexical_cast<string>(value);
}

template<typename T> // 1. Using stringstream
string StringFromIntegral_SS(T const &value) {
    static stringstream ss;
    ss.seekp(0l);
    ss.str("");
    ss << value;
    return ss.str();
}

template<typename T> // 3. Using c++11 to_string()
string StringFromIntegral_C11(T const &value) {
    return std::to_string(value);
}

template<typename T> // 3. Using c++11 to_string()
string StringFromIntegral_K(T const &value) {
    std::string result;
    result.reserve(10);

    static auto const gen = boost::spirit::traits::create_generator<T>::call();
    boost::spirit::karma::generate(back_inserter(result), gen, value);
    return result;
}
// -----------------------------------------------------------

// A wrapper to measure the different executions -------------
template<typename T, typename F>
long long MeasureExec(std::vector<T> const &v1, F const &func)
{
    return measure<>::execution(
        [&]() { for (auto const &i : v1) { func(i); }});
}
// -----------------------------------------------------------


int main()
{
    std::vector<int> v1(991908);
    std::mt19937 e2(1);
    std::uniform_int_distribution<> dist(3, 1440);
    std::generate(v1.begin(), v1.end(), [&]() { return dist(e2); });

    cout << "C++ 11 method " << 
        MeasureExec(v1, StringFromIntegral_C11<int>) << endl;
    cout << "String stream method " << 
        MeasureExec(v1, StringFromIntegral_SS<int>) << endl;
    std::cout << "Lexical cast method " << 
        MeasureExec(v1, StringFromIntegral_LC<int>) << endl;
    std::cout << "Spirit Karma method " << 
        MeasureExec(v1, StringFromIntegral_K<int>) << endl;

    return 0;
}
