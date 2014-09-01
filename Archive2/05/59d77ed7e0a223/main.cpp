#include <cstdio>
#include <cstdlib>

using namespace std;

const int n = 1024;
int a[n][n], b[n][n], c[n][n];
void mul()
{
    // 速いほう
    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k) {// ここと
            int v=a[i][k];
            for (int j = 0; j < n; ++j) // ここを入れ替えただけ
                c[i][j] += v * b[k][j];
        }
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
