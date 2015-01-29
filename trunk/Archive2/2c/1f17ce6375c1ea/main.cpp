#include <cstdio>

template<typename T>
T sum(T n) {
    T result = 0;
    for (T i = 0; i < n; ++i) {
        result += i;
    }
    return result;
}

int main()
{
    int x;
    scanf("%d", &x);
    printf("%d", sum(x));
    return 0;
}
