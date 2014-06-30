#include <iostream>

using namespace std;

struct A
{
    explicit operator bool() const
    {
        std::cout << "bool: ";
        return true;
    }

    operator int() const
    {
        std::cout << "int: ";
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
