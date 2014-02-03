#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string a = "acb";
    std::string b = "edf";
    std::string c(a.size() + b.size(), ' ');
    std::merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
    std::cout << c;
}