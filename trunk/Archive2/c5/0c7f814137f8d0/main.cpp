#include <iostream>

const char* test()
{
    bool b; // uninitialized

    switch (b)
    {
    case false:
        return "false";      // garbage was zero (zero is false)
    case true: 
        return "true";       // garbage was non-zero (non-zero is true)
    default:
        return "impossible"; // options are exhausted, this must be impossible...
    }
}

int main()
{
    std::cout << test() << std::endl;
}