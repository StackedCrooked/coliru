#include <boost/spirit/include/karma.hpp>
#include <boost/utility/string_ref.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <random>
#include <boost/lexical_cast.hpp>

using namespace std;
using Data = double;

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
    thread_local stringstream ss;
    ss.str("");
    ss.clear();
    ss << value;
    return ss.str();
}

template<typename T> // 3. Using c++11 to_string()
string StringFromIntegral_C11(T const &value) {
    return std::to_string(value);
}

template<typename T> // 4. Karma to string
std::string StringFromIntegral_K(T const &value) {
    thread_local auto const gen = boost::spirit::traits::create_generator<T>::call();
    thread_local char buf[20];
    char* it = buf;
    boost::spirit::karma::generate(it, gen, value);
    return std::string(buf, it);
}

template<typename T> // 5. Karma to string_ref
boost::string_ref StringFromIntegral_KSR(T const &value) {
    thread_local auto const gen = boost::spirit::traits::create_generator<T>::call();
    thread_local char buf[20];
    char* it = buf;
    boost::spirit::karma::generate(it, gen, value);
    return boost::string_ref(buf, it-buf);
}
// -----------------------------------------------------------

// A wrapper to measure the different executions -------------
template<typename T, typename F>
long long MeasureExec(std::vector<T> const &v1, F const &func)
{
    return measure<>::execution(
        [&]() { for (auto const &i : v1) { func(i); }});
        //[&]() { for (auto const &i : v1) { assert(func(i) == StringFromIntegral_LC(i)); }});
}
// -----------------------------------------------------------

int main()
{
    std::vector<Data> v1(991908);
    std::mt19937 e2(1);
    std::uniform_real_distribution<Data> dist;
    std::generate(v1.begin(), v1.end(), [&]() { return dist(e2); });

    cout << "C++ 11 method " << 
        MeasureExec(v1, StringFromIntegral_C11<Data>) << endl;
    cout << "String stream method " << 
        MeasureExec(v1, StringFromIntegral_SS<Data>) << endl;
    std::cout << "Lexical cast method " << 
        MeasureExec(v1, StringFromIntegral_LC<Data>) << endl;
    std::cout << "Spirit Karma method " << 
        MeasureExec(v1, StringFromIntegral_K<Data>) << endl;
    std::cout << "Spirit Karma method with string_ref " << 
        MeasureExec(v1, StringFromIntegral_KSR<Data>) << endl;

    return 0;
}

