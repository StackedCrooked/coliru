#include <iostream>

struct foo
{
    operator int() const
    {
        std::cout << "int\n";
        return 1;
    }
    
    operator long() const
    {
        std::cout << "long\n";
        return 1;
    }
};


int main()
{
    foo f;

    (void)(f == true);
}