#include <iostream>

void foo(int n) {
#pragma omp critical
        std::cout << n << "\n";
}

int main() {

    int i = 0;
#pragma omp parallel
    {
        foo(++i);
    }
}
