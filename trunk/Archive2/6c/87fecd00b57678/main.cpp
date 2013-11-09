#include <iostream>

using namespace std;

template<typename T, size_t N, size_t M>
void display(T (&a)[N][M])
{
    for(size_t R = 0; R < N; R++)
        for(size_t C = 0; C < M; C++)
            cout << a[R][C] << endl;
}

int main()
{
    char name[][20] = { "alex", "ben" };
    display(name);
    return 0;
}

