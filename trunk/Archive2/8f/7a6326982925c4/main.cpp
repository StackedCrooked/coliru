#include <iostream>

int main() {
    unsigned long long permutations = 0;
    int num_dots = 9;
    for(int i=1; i<=num_dots; ++i) {
        unsigned long long this_path = 1;
        for(int j=i; j<=num_dots; ++j) 
            this_path *= j;
        permutations += this_path;
    }
    std::cout << permutations;
}