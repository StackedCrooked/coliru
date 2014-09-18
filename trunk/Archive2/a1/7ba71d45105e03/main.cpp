
#include <iostream>
#include <bitset>

using namespace std;

int main()
{

    int n = 10;
    std::bitset<32> s(n);

    cout << n << " " << s << endl;

    return 0;
}