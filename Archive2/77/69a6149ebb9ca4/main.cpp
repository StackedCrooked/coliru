#include <algorithm>
#include <iostream>

inline double mean(int n, double *a) {
    return std::accumulate(a, a + n, 0) / n;
}

int main() {
    double t[] = {5, 7, 9};
    std::cout << mean(3, t) << std::endl;
}