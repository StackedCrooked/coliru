#include <iostream>

constexpr int something_expensive(int x) { return x; }

int process(int x)
{
    switch (x)
    {
        // hard-coded for common cases
        case 0: return something_expensive(0);
        case 1: return something_expensive(2);
        case 2: return something_expensive(2);
        
        // default is non-optimized
        default: return something_expensive(x);
    };
}

int main()
{   
}