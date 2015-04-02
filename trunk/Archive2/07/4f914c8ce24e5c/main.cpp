#include <vector>
#include <iostream>
using namespace std;

int main()
{
    volatile int a = 5;
    volatile int b = 6;
    cout << (4<= a <= b) << endl;
    return 0;
}
