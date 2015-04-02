#include <vector>
#include <iostream>
using namespace std;

int main()
{
    volatile int a = 5;
    cout << (4<= a <= 6) << endl;
    return 0;
}