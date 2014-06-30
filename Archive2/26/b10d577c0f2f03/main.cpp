#include <iostream>

using namespace std;

struct A
{
    explicit operator bool() const
    {
        std::cout << "bool: ";
        return true;
    }

    operator int() 
    {
        std::cout << "int: ";
        return 0;
    }
};

int main()
{
    auto const a = A();
    
    if (a)
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }
}
