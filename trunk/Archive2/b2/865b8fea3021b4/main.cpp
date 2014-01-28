#include <iostream>

struct foo
{
    operator bool() const //Explicit overload for bool
    {
        std::cout << "bool\n";
        return true; 
    }
    
    operator int() const
    {
        std::cout << "int\n";
        return 1;
    }
};


int main()
{
    foo f;

    (void)(f == true);
}