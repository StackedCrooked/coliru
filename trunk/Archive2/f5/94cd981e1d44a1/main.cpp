#include <iostream>
using namespace std;


void RowNumbers(int n, int max )
{
    if ( n < max )
    {
        cout << n << ' ';
        RowNumbers( n + 1, max );
    }
    cout << n << ' ';
}

void PrintRhombus(int n, int i = 1){
    if(i == 2 * n) return;
    int numbers_in_line = i < n ? i : 2 * n - i;
    int space = (n - numbers_in_line) * 2;
    cout << string( space, ' ' );
    RowNumbers( 1, numbers_in_line );
    cout << endl;
    PrintRhombus(n, i+1);
}

int main()
{
    int a;
    cout << "Enter a number [1-9]: " << endl;
    cin >> a;
    if (a > 0 && a < 10)
    {
        PrintRhombus( a );
    }
    else
        cout << "Wrong input." << endl;
}