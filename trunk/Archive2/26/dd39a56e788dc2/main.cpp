#include <iostream>
#include <string>
#include <vector>

class Blah
{
public:
    Blah()
    {
        std::cout << "Blah()" << std::endl;
    }
    Blah(const Blah&)
    {
        std::cout << "Blah(const Blah&)" << std::endl;
    }
    Blah(Blah&&)
    {
        std::cout << "Blah(Blah&&)" << std::endl;
    }
};


Blah do_it(Blah x)
{
    std::cout << "do_it" << std::endl;
    return x;
}


int main()
{
    Blah b;
    const Blah x = do_it(b);
    (void)x;
}
