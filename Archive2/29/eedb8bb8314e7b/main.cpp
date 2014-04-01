#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <boost/dynamic_bitset.hpp>

int main()
{
    using namespace std;
    int c = 44;
    cout << binary << c << endl;
    cout << binary << (c << (7-8)) << endl;
}
