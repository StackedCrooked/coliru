#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

string operator""hi(unsigned long long i)
{
    string s;
    for (; i; i--)
        s += "hi ";
    return s;
}

int main()
{
    cout << 10hi << endl;
    return 0;
}