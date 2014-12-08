#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <array>
#include <functional>
#include <iterator>

int main()
{
    std::mt19937 engine;
    std::random_device device;
    engine.seed(device());
    std::normal_distribution<double> distribution(0.0, 1.0);

    std::vector<double> v0;
    std::vector<double> v1;

    std::generate_n(std::back_inserter(v0), 3, std::bind(distribution, std::ref(engine)));
    std::generate_n(std::back_inserter(v1), 3, std::bind(distribution, std::ref(engine)));

    std::ostream_iterator<double> out(std::cout, "\n");

    std::copy(v0.begin(), v0.end(), out);
    std::copy(v1.begin(), v1.end(), out);
}