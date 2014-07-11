#include <iostream>
#include <vector>
#include <array>
#include <omp.h>

inline unsigned f(const unsigned x) {
    return 1664525 * x + 1013904223;   
}

#define for_each_vertex(_condition_, x, xmax, pragmaopts, stuff) \
switch(_condition_) { \
case 0x2d2: \
_Pragma(pragmaopts) \
    for (int x1 = 0; x1 < xmax[1]; x1++) { \
        for (int x0 = (x1 & 1); x0 < xmax[0]; x0+=2) { \
            const std::array<int,2> x{x0,x1}; \
            stuff \
        } \
    } \
_Pragma(pragmaopts) \
    for (int x1 = 0; x1 < xmax[1]; x1++) { \
        for (int x0 = !(x1 & 1); x0 < xmax[0]; x0+=2) { \
            const std::array<int,2> x{x0,x1}; \
            stuff \
        } \
    } \
break; \
}
    
inline int move_linear(const int dx, const int x, const int xmax) {
    if (dx < 0) return x + dx + xmax * (x < -dx);
    else        return x + dx - xmax * (x > xmax - 1 - dx);
}

template<typename T>
inline int nn(const T x, const int L, const int element) {
    switch(element) {
    case 'n':   return 2;
    case   0:   return (x[0])                             + L * x[1];
    case  -1:   return move_linear(-1,x[0],L)   + L * (x[1]);
    case  +1:   return (x[0] == (L - 1) ? 0 : x[0] + 1)   + L * (x[1]);
    case  -2:   return (x[0])                             + L * (x[1] == 0 ? (L - 1) : x[1] - 1);
    case  +2:   return (x[0])                             + L * (x[1] == (L - 1) ? 0 : x[1] + 1);
    case  -3:   return (x[0] == 0 ? (L - 1) : x[0] - 1)   + L * (x[1] == 0 ? (L - 1) : x[1] - 1);
    case  +3:   return (x[0] == (L - 1) ? 0 : x[0] + 1)   + L * (x[1] == (L - 1) ? 0 : x[1] + 1);
    default:    return 0;
    }
}

void myfunc(std::vector<unsigned>& v, const int L, const int N) {
    std::array<int,2> xmax{L,L};
    for_each_vertex(22, x, xmax, "omp parallel for",
        const int vi = v[nn(x, L, 0)];
        unsigned sum = 0;
        for (int z = 1; z <= nn(x, L, 'n'); z++) {
            sum += v[nn(x, L, -z)];
            sum += v[nn(x, L, +z)];
        }
        v[nn(x, L, 0)] = f((vi & 2) + sum);    
    )
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
