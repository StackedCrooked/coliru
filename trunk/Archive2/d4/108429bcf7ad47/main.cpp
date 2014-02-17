#include <algorithm>
#include <deque> 
#include <fstream> 
#include <iostream>
#include <iterator> 
#include <string>

bool hasEven(const std::string &s) {
    return s.size() % 2 == 0;
}

int main() {
    std::ofstream evens("evens.out"), odds("odds.out");
    if (!evens || !odds) {
        std::cerr << "ERROR\n";
    }
    
    std::istream_iterator<std::string> first(std::cin), last;
    std::deque<std::string> evenTokens, oddTokens;
    
    std::partition_copy(first, last, std::back_inserter(evenTokens), std::front_inserter(oddTokens), hasEven);
    std::copy(evenTokens.begin(), evenTokens.end(), std::ostream_iterator<std::string>(evens, "\n"));
    std::copy(oddTokens.begin(), oddTokens.end(), std::ostream_iterator<std::string>(odds, "\n"));
}
