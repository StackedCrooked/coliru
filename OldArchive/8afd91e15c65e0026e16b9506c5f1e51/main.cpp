#include <cstdlib>
#include <ctime>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

int main() {
    
    std::srand(std::time(0));
    
    std::vector<int> random(30);
    
    int min = 3, max = 19;
    
    std::transform(std::begin(random), std::end(random), std::begin(random), [=](int) {
        return min + (std::rand() % (max - min + 1));
    });
    
    std::copy(std::begin(random), std::end(random), std::ostream_iterator<int>(std::cout, "\n"));
    
}