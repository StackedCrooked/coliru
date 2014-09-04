#include <chrono>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <utility>
#include <random>

static void make_killer(int size, std::vector<int>& v) {
    int candidate = 0;
    int num_solid = 0;
    int gas = size - 1;

    std::vector<int> tmp(size);
    v.resize(size);

    for (int i = 0; i < size; ++i) {
        tmp[i] = i;
        v[i] = gas;
    }

    std::sort(tmp.begin(), tmp.end(), [&](int x, int y) {
        if (v[x] == gas && v[y] == gas) {
            if (x == candidate) v[x] = num_solid++;
            else v[y] = num_solid++;
        }

        if (v[x] == gas) candidate = x;
        else if (v[y] == gas) candidate = y;

        return v[x] < v[y];
    });
}

int main() {
    std::cout << LIBRARY << '\n';
    constexpr int N = 256;
    std::vector<int> arr;
//    worst_case_fill(std::begin(arr), std::end(arr), [] { thread_local int i = 0; return S{++i}; });
    make_killer(N, arr);
    //std::rotate(std::begin(arr), std::begin(arr) + 1, std::end(arr));
    
    std::cout << "worst case: ";
    std::copy(std::begin(arr), std::end(arr),
      std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
    
    int count = 0;
    std::sort(std::begin(arr), std::end(arr), [&] (auto l, auto r) { ++count; return l < r; });

    std::cout << "comparisons in worst case: " << count << '\n';
    
    make_killer(N, arr);
    std::rotate(std::begin(arr), std::begin(arr) + 1, std::end(arr));
    
    count = 0;
    std::sort(std::begin(arr), std::end(arr), [&] (auto l, auto r) { ++count; return l < r; });
    
    std::cout << "comparisons in rotated worst case: " << count << '\n';

    count = 0;
    std::sort(std::begin(arr), std::end(arr), [&] (auto l, auto r) { ++count; return l < r; });
    std::cout << "comparisons in sorted case: " << count << '\n';

    
    count = 0;
    std::shuffle(std::begin(arr), std::end(arr), std::mt19937{});
    std::sort(std::begin(arr), std::end(arr), [&] (auto l, auto r) { ++count; return l < r; });
    
    std::cout << "comparisons in shuffled case: " << count << '\n';

}