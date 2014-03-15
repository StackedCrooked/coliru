#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int main() {
    // Your original vector
    auto original = { 2, 2, 2, 4, 4 };
    
    // Sort numbers and remove duplicates (in a copy, because std::unique modifies the contents)
    std::vector<int> uniques(original);
    std::sort(std::begin(uniques), std::end(uniques));
    auto end = std::unique(std::begin(uniques), std::end(uniques));
    
    // Count occurences of each number in the original vector
    // The key is the number of occurences of a number, the value is the number
    std::map<int, int> population;
    
    for (auto i = uniques.begin(); i != end; ++i) {
        population.emplace(std::count(std::begin(original), std::end(original), *i), *i);
    }
    
    std::cout << population.begin()->second;
}