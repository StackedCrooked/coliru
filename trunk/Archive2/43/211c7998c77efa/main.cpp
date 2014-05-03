#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <climits>

static const int num_iterations = 10;
static const int num_elements = 30000000;

int main() {
    std::vector<char> data(num_elements);
    std::vector<char> dest(num_elements/2);
    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<char> dist{0, 15};
    std::generate(data.begin(), data.end(), [&](){return dist(gen);});
    
    for(unsigned i=0; i<num_iterations; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        
        unsigned lim = dest.size();
        unsigned char *begin = &data[0];
        unsigned char *end = &data[0]+num_elements;
        unsigned char *dst = &dest[0];
        while(begin != end) {
            char c = *begin++;
            *packed++ = (c<<4) | (*begin++);
        }
             
        auto stop = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
        std::cout << +dest[dest.size()-1] << " took " << dur.count() << "us\n";
    }
}
