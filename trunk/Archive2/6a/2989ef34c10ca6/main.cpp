#include <iostream>
#include <vector>
#include <string>
using namespace std;

auto operator""_times(unsigned long long n)
{
    return [n](const string &s) {
        string _s = s;
        for (auto i = n - 1; i; i--)
            _s += ", " + s;
        return _s;
    };
}

auto main() -> int
{
    auto hello = [](const string &c) { cout << "Hello, " << c << "!" << endl; };
    vector<string> cities = {"Sao Paulo", "Campinas"};
    for (auto city : cities)
        hello(3_times(city));
    return 0;
}