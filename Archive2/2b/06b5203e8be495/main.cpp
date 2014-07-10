#include <iostream>
#include <vector>
#include <omp.h>

inline unsigned f(const unsigned x) {
    return 1664525 * x + 1013904223;   
}

void myfunc(std::vector<unsigned>& v, const int L, const int N) {
    #pragma omp parallel for
    for (int x1 = 0; x1 < L; x1++) {
        for (int x0 = (x1 & 1); x0 < L; x0+=2) {
            const int vi = v[x0 + L * x1];
            const int v1 = v[(x0 == 0 ? (L - 1) : x0 - 1) + L * (x1)];
            const int v2 = v[(x0 == (L - 1) ? 0 : x0 + 1) + L * (x1)];
            const int v3 = v[(x0) + L * (x1 == 0 ? (L - 1) : x1 - 1)];
            const int v4 = v[(x0) + L * (x1 == (L - 1) ? 0 : x1 + 1)];
            v[x0 + L * x1] = f((vi & 2) + (v1 + v2 + v3 + v4));    
        }
    }
    #pragma omp parallel for
    for (int x1 = 0; x1 < L; x1++) {
        for (int x0 = !(x1 & 1); x0 < L; x0+=2) {
            const int vi = v[x0 + L * x1];
            const int v1 = v[(x0 == 0 ? (L - 1) : x0 - 1) + L * (x1)];
            const int v2 = v[(x0 == (L - 1) ? 0 : x0 + 1) + L * (x1)];
            const int v3 = v[(x0) + L * (x1 == 0 ? (L - 1) : x1 - 1)];
            const int v4 = v[(x0) + L * (x1 == (L - 1) ? 0 : x1 + 1)];
            v[x0 + L * x1] = f((vi & 2) + (v1 + v2 + v3 + v4));    
        }
    }
    return;
}

int main(int argc, char** argv) {
    const int L = 1000;
    const int N = L * L;
    std::vector<unsigned> v(N, 0);
    for (unsigned i = 0; i < v.size(); i++) {
        v[i] = 2 * i + (i & 6) + 1;   
    }
    double start = omp_get_wtime();
    for (int t = 0; t < 1000; t++) {
        myfunc(v, L, N);
    }
    double end = omp_get_wtime();
    std::cout << end - start << std::endl;
    double sum = 0.0;
    #pragma omp parallel for reduction (+:sum)
    for (int i = 0; i < N; i++) {
        sum += 2 * (2.32830643653869629E-10 * v[i]) - 1;   
    }
    std::cout << "sum = " << sum << std::endl;
    return 0;   
}
