#include <deque>
#include <iostream>
#include <fstream>
#include <algorithm>

uint64_t fibd(int n, int m) {
    std::deque<uint64_t> rabbits;
    rabbits.push_back(1);
    std::generate_n(std::back_inserter(rabbits), m - 1, []() { return 0; });

    for(int i = 0; i < n - 1; ++i) {
        // add up the back
        auto&& sum = std::accumulate(rabbits.begin() + 1, rabbits.end(), 0ULL);
        rabbits.push_front(sum);

        // death
        rabbits.pop_back();
    }

    return std::accumulate(rabbits.begin(), rabbits.end(), 0LL);
}

int main() {
//    std::ifstream in("rosalind_fibd.txt");
//    int n, m;
//    in >> n >> m;
//    std::cout << fibd(n, m);
    std::cout << fibd(89, 19);
}