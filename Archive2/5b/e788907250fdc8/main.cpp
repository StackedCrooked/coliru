#include <cstdio>
#include <cstdlib>

using namespace std;

const int n = 2048;
int a[n][n], b[n][n], c[n][n];
void mul()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                c[i][j] += a[i][k] * b[k][j];
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
    printf("%d\n", a[114][514]);
}
