#include <iostream>
#include <random>

int main(int, char*[]) {
    std::random_device rnd_dev;
    std::mt19937 gen(rnd_dev());
    long double precision = 0.000001;
    std::uniform_real_distribution<long double> dis(precision, 1.0 - precision);
    
    for (int i = 0; i < 10; ++i)
        std::cout << dis(gen) << '\n';
    return 0;
}