#include <sstream>
#include <iostream>

using namespace std;

int main()
{
    ostringstream os1;
    ostringstream os2;

    os1 << 1 << " " << 2;
    os2 << 1 << " " << 2 << " " << 3;

    auto s = os1.str();  
    const char *p = s.c_str(); //s is not a temporary object anymore!

    cout << os2.str() << endl;
    cout << p << endl;

    return 0;
}