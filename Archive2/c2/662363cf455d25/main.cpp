#include <iostream>
#include <climits>
#include <cinttypes>
using namespace std;

int main()
{
    uint16_t i = 0;
    cout << USHRT_MAX << '\n' << (uint16_t)(i - 1) << '\n';
    cout << USHRT_MAX << '\n' << i - 1 << '\n';
}