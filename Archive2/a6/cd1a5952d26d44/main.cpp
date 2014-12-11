#include <iostream>
#include <vector>
#include <string>
using namespace std;

auto main() -> int
{
    auto hello = [](const string &c) { cout << "Hello, " << c << "!" << endl; };
    vector<string> cities = {"Sao Paulo", "Campinas"};
    for (auto city : cities)
        hello(city);
}