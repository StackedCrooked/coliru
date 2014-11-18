#include <random>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <iostream>

int main() {
    std::mt19937 mt;
    std::uniform_int_distribution<> dist;
    
    std::vector<int> v;
    generate_n(back_inserter(v), 10000, bind(dist,ref(mt)));

    nth_element(begin(v), begin(v) + 10, end(v));
    v.erase(begin(v) + 10, end(v));
    
    std::cout << "The ten smallest values out of 10,000 values generated: ";
    copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, " "));
}
