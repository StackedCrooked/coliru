#include <cstdio>

#define N 3

struct Data {
    int A[N][N];
    int B[N];
};

int foo(int uloc, const int A[N][N], const int B[N])
{
    for(unsigned int j = 0; j < N; j++) {
        for( int i = 0; i < N; i++) {
            for( int r = 0; r < N ; r++) {
                for( int q = 0; q < N ; q++) {
                   uloc += B[i]*A[r][j] + B[j];
                }
            }
        }
    }
    return uloc;
}

int apply(const Data *d)
{
    return foo(4,d->A,d->B);
}

int main(int, char **)
{
    Data d;

    int res = 11 + apply(&d);

    printf("%d\n",res);
    return 0;
}