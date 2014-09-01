#include <cstdio>
#include <cstdlib>

using namespace std;

const int n = 1024;
int a[n][n], b[n][n], c[n][n];
void mul()
{
    for (int i = 0; i < n; i += 8)
        for (int j = 0; j < n; j += 8)
            for (int k = 0; k < n; ++k)
                for (int ii = i; ii < i + 8; ++ii)
                    for (int jj = j; jj < j + 8; ++jj)
                        c[ii][jj] += a[ii][k] * b[k][jj];
}
int main()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            a[i][j] = rand();
            b[i][j] = rand();
        }
    }

    mul();
    printf("%d\n", a[19][19]);
}
