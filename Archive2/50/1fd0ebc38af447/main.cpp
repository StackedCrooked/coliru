// import random;
// for i in range(2,17): print "[0,{}):\t{}".format(i,random.randrange(i))

#include <cstdio>
#include <random>
#include <algorithm>

struct random_device_seed_seq {    
    std::random_device random_device;
    
    template<typename InputIterator>
    void generate(InputIterator rb, InputIterator re) {
        std::generate(rb, re, std::ref(random_device));
    }
};

int main() {
    random_device_seed_seq seed;
    std::mt19937 eng(seed);
    std::uniform_int_distribution<> dist;
    using param = std::uniform_int_distribution<>::param_type;
   
    for (int i = 2; i < 17; ++i)
        std::printf("[0,%d):\t%d\n", i, dist(eng, param{0, i-1}));
}
