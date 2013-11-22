#include <iostream>
#include <stdint.h>


int main()
{
    typedef void(*Printer)(int);
    Printer printers[] = {
        +[](int i){ std::cout << i; },
        +[](int i){ std::cout << "Fizz"; },
        +[](int i){ std::cout << "Buzz"; },
        +[](int i){ std::cout << "FizzBuzz"; }
    };

    for (int i = 1; i <= 100; ++i)
    {
        int n = ((i % 3 == 0) << 0) | ((i % 5 == 0) << 1);
        std::cout
            << "i=" << i
            << "\tn=" << n
            << '\t' << ((printers[n](i)), ' ')
            << std::endl;
    }
}