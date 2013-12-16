#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

using element_t = std::tuple<int, std::string, std::string>;

int main() {
    std::vector<element_t> vec;
    vec.emplace_back(0, "red", "charming");
    vec.emplace_back(0, "red", "charming");
    vec.emplace_back(0, "green", "not-charming");
    vec.emplace_back(0, "green", "charming");
    vec.emplace_back(0, "red", "not-charming");
    
    int all     = std::count_if(vec.begin(), vec.end(), [](const element_t& ell) { return true; });
    int reds    = std::count_if(vec.begin(), vec.end(), [](const element_t& ell) { return std::get<1>(ell) == "red"; });
    std::cout << "All: " << all << '\n';
    std::cout << "Reds: " << reds << '\n';
}
