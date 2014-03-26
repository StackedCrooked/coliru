#include <iostream>
#include <climits>
#include <cassert>

unsigned long long perm(int num_dots) {
    unsigned long long permutations = 0;
    for(int i=1; i<=num_dots; ++i) {
        unsigned long long this_path = 1;
        for(int j=i; j<=num_dots; ++j) {
            assert(ULLONG_MAX/j>=this_path);
            this_path *= j;
        }
        assert(ULLONG_MAX-this_path>=permutations);
        permutations += this_path;
    }
    return permutations;
}

int main() {
    std::cout << perm(3*3) << '\n';
    std::cout << perm(4*4) << '\n';
    std::cout << perm(5*5) << '\n';
}