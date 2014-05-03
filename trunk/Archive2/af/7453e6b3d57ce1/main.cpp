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
template<typename T> // A. Using stringstream ================
string StringFromNumber_SS(T const &value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

template<typename T> // B. Using boost::lexical_cast =========
string StringFromNumber_LC(T const &value) {
    return boost::lexical_cast<string>(value);
}

template<typename T> // C. Using c++11 to_string() ===========
string StringFromNumber_C11(T const &value) {
    return std::to_string(value);
}
// ===========================================================

// 3. A wrapper to measure the different executions ----------
template<typename T, typename F>
long long MeasureExec(std::vector<T> const &v1, F const &func)
{
    return measure<>::execution([&]() {
        for (auto const &i : v1) {
            if (func(i) != StringFromNumber_LC(i)) {
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
    std::mt19937 e2(1);
    std::uniform_int_distribution<> dist(3, 1440);
    std::generate(v.begin(), v.end(), [&]() { return dist(e2); });
}

template<typename T>
typename std::enable_if<!std::is_integral<T>::value>::type 
FillVec(vector<T> &v)
{
    std::mt19937 e2(1);
    std::uniform_real_distribution<> dist(-1440., 1440.);
    std::generate(v.begin(), v.end(), [&]() { return dist(e2); });
}
// -----------------------------------------------------------

int main()
{
    std::vector<int> v1(991908);
    FillVec(v1);

    cout << "C++ 11 method ......... " <<
        MeasureExec(v1, StringFromNumber_C11<int>) << endl;
    cout << "String stream method .. " <<
        MeasureExec(v1, StringFromNumber_SS<int>) << endl;
    cout << "Lexical cast method ... " <<
        MeasureExec(v1, StringFromNumber_LC<int>) << endl;

    return 0;
}