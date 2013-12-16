#include <iostream>


using namespace std;

int main()
{
    const int N = 4;
    for (int i=N; i>=0; i--)
    {
        for (int j=0; j<i; j++)
            cout << "*";

        for (int k=0; k<(N-i)*2+7; k++)
            cout << " ";

        for (int j=0; j<i; j++)
            cout << "*";

        cout << endl;
    }
}

