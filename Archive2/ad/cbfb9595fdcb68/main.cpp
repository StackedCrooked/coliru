#include <iostream>

typedef char state_type[64];


int
main ()
{
    std::cout << sizeof (state_type) << "\n";
    state_type state = state_type ();
}
