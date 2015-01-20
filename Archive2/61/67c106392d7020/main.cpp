#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iostream>

using namespace std;

int main() {
    vector<double> v;
    // generate some data
    generate_n(back_inserter(v), 1ul << 18, bind(uniform_real_distribution<double>(0,1.0), default_random_engine { random_device {}() }));

    long double sum = 0;

    {
#pragma omp parallel for reduction(+:sum)
        for(size_t i = 0; i < v.size(); i++)
        {
            sum += v[i];
        }
    }
    std::cout << "Done: sum = " << sum << "\n";
}
