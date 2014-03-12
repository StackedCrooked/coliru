#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <thread>
#include <future>
#include <cstdint>

using namespace std;

std::intmax_t parallel_sum(vector<int> const& V) {
    auto const mid = begin(V) + V.size() / 2;
    
    auto sum1 = std::async([&V, mid](){
      return std::accumulate(begin(V), mid, std::intmax_t(0));
    });
    
    auto sum2 = std::accumulate(mid, end(V), std::intmax_t(0));
    return sum1.get() + sum2;
}

int main() {
    std::vector<int> V (10000000);
    std::generate(begin(V), end(V), &rand);
    cout << parallel_sum(V);
}