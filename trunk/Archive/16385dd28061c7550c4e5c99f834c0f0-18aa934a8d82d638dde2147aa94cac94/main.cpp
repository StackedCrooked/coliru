#include <algorithm>
#include <vector>
#include <array>
#include <iostream>

void do_test(std::vector<int> data) {
    for(unsigned i=0; i<data.size(); ++i)
        std::cout << data[i] << ' ';
    std::cout << '\n';
}

void do_minimal_tests() {
    std::array<std::vector<int>,15> sets = {{
        {0},
        {0, 0},
        {0, 1},
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 1},
        {0, 1, 2},
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 1},
        {0, 1, 1, 1},
        {0, 0, 1, 2},
        {0, 1, 1, 2},
        {0, 1, 2, 2},
        {0, 1, 2, 3}
    }};
    for(unsigned i=0; i<sets.size(); ++i) {        
        std::vector<int> t=sets[i];
        do {
            do_test(static_cast<std::vector<int>&>(t));
        }while(std::next_permutation(t.begin(),t.end()));
    }
}

int main() {
    do_minimal_tests();
}