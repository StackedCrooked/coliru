#include <vector>
#include <iostream>
using namespace std;

#define L 4
#define U 6

int main()
{
    volatile int a = 5;
    cout << (L <= a <= U) << endl;
    return 0;
}
