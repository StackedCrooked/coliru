#include <iostream>
#include <vector>
#include <bitset>
#include <omp.h>

int L = 10;
int N = L * L;
int T = 100;
std::vector<int> lx;
std::vector<int> vol;
std::vector<std::bitset<2>> wsfpf;
std::vector<int> a;

inline void get_index1(int& j, int x, int y, int k) {
    j = x + lx[0] * y + vol[k] * (k - lx[k] * (x == lx[k] - 1));
    return;
}

inline void get_index2(int& j, int i, int k) {
    j = i + vol[k] * (k - lx[k] * wsfpf[i][k]);
    return;
}

int main(int argc, char** argv) {
    if (3 == argc) {
        L = std::atoi(argv[1]);
        T = std::atoi(argv[2]);
    }

    std::cout << "L = " << L << "\t"
              << "T = " << T << "\t"
              << "threads = " << omp_get_max_threads() << "\t"
              << std::endl;
    
    lx.resize(2); 
    lx[0] = L; lx[1] = L;
    vol.resize(2);
    vol[0] = 1; vol[1] = lx[0];
    N = lx[0] * lx[1];
    wsfpf.resize(N);
    a.resize(N);
    
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < 2; k++) {
            int x = (i / vol[k] ) % lx[k];
            if (x == lx[k] - 1)
                wsfpf[i].set(k, true);
            else
                wsfpf[i].set(k, false);
        }
     }   
    
    double start, end;
    
    start = omp_get_wtime();
    for (int t = 0; t < T; t++) {
        #pragma omp parallel for
        for (int y = 0; y < lx[1]; y++) {
            for (int x = 0; x < lx[0]; x++) {
                int j;
                int i = x + lx[0] * y;
                get_index1(j, x, y, (i * i) & 1);
                a[i] += (j & 1) + (a[i] & 2);
            }
        }
    }
    end = omp_get_wtime();
    std::cout << "xy based: " << end - start << std::endl;

    start = omp_get_wtime();
    for (int t = 0; t < T; t++) {
        #pragma omp parallel for
        for (int i = 0; i < N; i++) {
            int j;
            get_index2(j, i, (i * i) & 1);
            a[i] += (j & 1) + (a[i] & 2);
        }
    }
    end = omp_get_wtime();
    std::cout << "i based: " << end - start << std::endl;

    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += a[i] & 1;
    }
    std::cout << sum << std::endl;

    return 0;
}