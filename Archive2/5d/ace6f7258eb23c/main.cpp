#include <iostream>
#include <vector>
#include <algorithm>

struct element {
    element() = default;
    
    element(element&&) = default;
    element& operator=(element&&) = default;
    
    element(const element&) = delete;
    element& operator=(const element&) = delete;
    
    //int n;   // => fail
    int n = 0; // => ok
};

int main() {
    std::vector<element> source(10), destination;
    std::move(std::begin(source), std::end(source), std::back_inserter(destination)); // will it work?
}