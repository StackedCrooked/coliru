#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
    string a("123");
    string x;
    if (istringstream(a) >> x) cout << x << endl;
    return 0;
}