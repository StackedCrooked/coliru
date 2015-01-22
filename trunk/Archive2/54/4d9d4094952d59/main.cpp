#include <omp.h>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    vector<double> v;
    // generate some data
    generate_n(back_inserter(v), 1ul << 18, bind(uniform_real_distribution<double>(0,1.0), default_random_engine { random_device {}() }));

    auto step_size   = 100ul;
    auto total_steps = v.size() / step_size + 1;

    size_t steps_completed = 0;
    long double sum = 0;

#pragma omp parallel 
    {
        size_t local_count = 0;


#pragma omp for reduction(+:sum)
        for(size_t i = 0; i < v.size(); i++)
        {
            sum += v[i];

            if (local_count++ % step_size == step_size-1)
            {
#pragma omp atomic
                ++steps_completed;
                
                if (steps_completed % 100 == 1)
                {
#pragma omp critical
                    std::cout << "Progress: " << steps_completed << " of " << total_steps << " (" << std::fixed << std::setprecision(1) << (100.0*steps_completed/total_steps) << "%)\n";
                }
            }
        }
    }
    std::cout << "Done: sum = " << sum << "\n";
}
