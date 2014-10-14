#include <string>
#include <regex>
#include <iostream>

int main()
{
using namespace std::regex_constants;
std::string str("{trol,asdfsad},{safsa, aaaaa,aaaaadfs}");
std::smatch m;
std::regex r("\\{(.*)\\}");   // matches anything between {}

std::cout << "Initiating search..." << std::endl;
while (std::regex_search(str, m, r)) {
    for (auto x : m) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    str = m.suffix().str();
}
}