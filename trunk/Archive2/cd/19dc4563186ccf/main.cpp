#include <iostream>
using namespace std;

int main()
{
    // declaring the arrays
    int page[30][100];

    // printing out example values
    cout << "\n" << page[1][30];       // returns :  -858993460 
    cout << "\n" << page[18][18];      // returns :  -858993460 
    cout << "\n" << page[42][42];      // returns :   3014706 
    cout << "\n" << page[1][102];      // returns :  -858993460 

    return 0;
}