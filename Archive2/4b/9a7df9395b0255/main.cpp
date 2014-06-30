#include <iostream>

using namespace std;

struct A
{
    explicit operator bool() const
    {
        return true;
    }

    operator int() const
    {
        return 0;
    }
};

int main()
{
    if (A())
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }
}
