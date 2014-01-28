#include <iostream>

struct foo
{
    operator int() const
    {
        std::cout << "int\n";
        return 1;
    }
    
    operator bool() const
    {
        std::cout << "bool\n";
        return 1;
    }
};


int main()
{
    foo f;

    (void)(f == true);
}