#include <cstdio>

double p, a[27][27], pw[27], pw1[27];
double dp[27];
int main() {
    //ios::sync_with_stdio(false);
    freopen("C:\\Users\\Sunny\\Documents\\C++/input.txt", "r", stdin);
    freopen("C:\\Users\\Sunny\\Documents\\C++/output.txt", "w", stdout);
    a[0][0] = 1.0;
    for (int i = 1; i <= 20; i++) {
        a[i][0] = 1.0;
        for (int j = 1; j <= i; j++)
            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
    }
    p = 0.1;
    pw[0] = 1.0;
    for (int i = 0; i <= 20; i++)
        pw[i] = p * pw[i - 1];
    pw1[0] = 1.0;
    for (int i = 1; i <= 20; i++)
        pw1[i] = (1 - p) * pw1[i - 1];
    dp[0] = 0.0;
    for (int i = 0; i <= 20; i++) {
        double tmp = 1;
        for (int j = 0; j <= i - 1; j++)
            tmp += a[i][i - j] * pw1[j] * pw[i - j] * dp[j];
        dp[i] = tmp / (1 - pw1[i]);
    }
    printf("%0.5f\n", dp[20]);
}
