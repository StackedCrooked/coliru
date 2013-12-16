#include <iostream>


using namespace std;

int main()
{
    const int ROW = 4;
    const int GAP = 7;
    for (int i=ROW, gap=GAP; i>=0; i--, gap+=2)
    {
        for (int j=0; j<i; j++)
            cout << "*";

        for (int k=0; k<gap; k++)
            cout << " ";

        for (int j=0; j<i; j++)
            cout << "*";

        cout << endl;
    }
}

