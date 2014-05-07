#include <iostream>
int main() {
    int i;
    int k;
    int sum1[5];
    int sum2[5];
    int a[5];

    for (i = 0; i <= 4; i++)
    {
        for (k = 0; k <= 4; k++)
        {
            sum1[i] = sum1[i] + a[k];
            sum2[k] = sum2[k] + a[i];
        }
    }
    std::cout << "Works!\n";
}