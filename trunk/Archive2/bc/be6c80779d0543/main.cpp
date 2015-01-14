#include <cstdio>

int main() {
    int tans = 0;
    scanf("%d",&tans);
    for (int i = 0; i < 100000; ++i)
        for (int id = 0; id < 10000; ++id) {
            tans++;
        }
    printf("%d\n", tans);
}
