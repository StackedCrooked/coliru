#include <algorithm>
#include <iostream>
#include <vector>

void make_killer(int size, std::vector<int>& v) {
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

int main(int argc, char** argv) {
    std::vector<int> v;
    int comparison_count;

    auto counter = [&](int x, int y) { ++comparison_count; return x < y; };

    std::cout << "N: comparisons\n";
    for (int i = 100; i <= 6400; i *= 2) {
        // to nullify small constants we multiply by 100
        make_killer(i, v);

        comparison_count = 0;
        std::sort(v.begin(), v.end(), counter);
        std::cout << i << ": " << comparison_count << "\n";
    }

    return 0;
}
