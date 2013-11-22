#include <iostream>
#include <random>

int main(int, char*[]) {
    const int range_from  = 0;
    const int range_to    = 10;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to);
 
    for (int i = 0; i < 10; ++i)
        std::cout << distr(generator) << '\n';
}