#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

int main()
{
    std::string text = "15555555.2587";
    std::stringstream ss;

    double number;
    ss << text;
    ss >> number;

    std::cout << std::fixed << std::setprecision(4) << number;
}