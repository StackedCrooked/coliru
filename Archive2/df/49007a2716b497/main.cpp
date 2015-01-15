#include <cstdio>

int main() {
    int tans = 0;
    for (int i = 0; i < 100000; ++i)
        #pragma omp parallel for reduction(+:tans)
        for (int id = 0; id < 10000; ++id) {
            tans++;
        }
    printf("%d\n", tans);
}
