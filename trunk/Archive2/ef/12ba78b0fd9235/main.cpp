#include <sstream>
#include <iostream>

using namespace std;

int main()
{
    ostringstream os1;
    ostringstream os2;

    os1 << 1 << " " << 2;
    os2 << 1 << " " << 2 << " " << 3;

    const char *p = os1.str().c_str();

    cout << os2.str() << endl;
    cout << p << endl;

    return 0;
}