#include <iostream>
#include <random>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>

using namespace std;

template<typename Generator>
void getrands(vector<double>& x, Generator& gen, unsigned num)
{
  generate_n(std::back_inserter(x), num, std::ref(gen));
}


int main()
{
    uniform_real_distribution<double> unif(0.0,1.0);
    mt19937 re(std::random_device{}());
    auto generator = bind(unif, std::ref(re));
    
    vector<double> vs;
    
    getrands(vs, generator, 10);
    for(auto const& v : vs) {
        cout << v << ' ';
    }
    cout << '\n';
    
    getrands(vs, generator, 10);
    for(auto const& v : vs) {
        cout << v << ' ';
    }
    cout << '\n';
}
