#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>

int priority(const std::string& s) {
    if (s=="Mike") return 0;
    if (s=="Cathy") return 1;
    if (s=="James") return 2;
    if (s=="Albert") return 3;
    if (s=="Austin") return 4;
    return 5;
}
const auto name_compare = [](const std::string& left, const std::string& right)->bool 
{
    int d = priority(left)-priority(right);
    if (d) return d<0;
    return left < right;
};

int main() {
    std::vector<std::string> names = {"Conan","Cary","Clarence","Cathy","Mike","Blake","Baron","Vaughan","Albert","Gabriel","Cathy"};
    std::sort(names.begin(), names.end(), name_compare);
    std::copy(names.begin(), names.end(), std::ostream_iterator<std::string>(std::cout," "));
}