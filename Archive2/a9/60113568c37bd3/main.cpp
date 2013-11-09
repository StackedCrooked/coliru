#include <iostream>

using namespace std;

void Display(char A[][20], int N, int M);

int main()
{
    char name[][20] = { "alex", "ben" };
    Display(name, 2, 20);
    return 0;
}

void Display(char A[][20], int N, int M)
{
    for(int R = 0; R < N; R++)
    {
        for(int C = 0; C < M; C++)
        {
            if (0 == A[R][C]) 
                break;
            cout << A[R][C] << endl;
        }
    }
}
