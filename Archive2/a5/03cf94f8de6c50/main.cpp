#include <boost/random.hpp>

#include <iostream>
#include <vector>
#include <iterator>

int main() {
    // This is an example of how _not_ to seed mt19937
    
    std::vector<int> seeds(624, 42);
    
    auto begin = std::begin(seeds);
    boost::mt19937 eng(begin, std::end(seeds));
    
    for (int i = 0; i < 10; ++i)
      std::cout << eng() << '\n';
}