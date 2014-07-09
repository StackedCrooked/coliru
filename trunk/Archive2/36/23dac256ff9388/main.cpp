#include <iostream>
#include <vector>
#include <algorithm>

class element {
    element(element&&) = default;
    element& operator=(element&&) = default;
    
    element(const element&) = delete;
    element& operator=(const element&) = delete;
};

int main() {
    std::vector<element> source(10), destination;
    std::move(std::begin(source), std::end(source), std::back_inserter(destination)); // will it work?
}