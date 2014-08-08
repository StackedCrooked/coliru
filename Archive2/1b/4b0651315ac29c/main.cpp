#include <iostream>
#include <stdexcept>


void handle_unexpected()
{
    // Salvage the situation!
    throw short();
}


void throw_short() throw(short)
{
    throw long();
}


int main()
{
    std::set_unexpected(handle_unexpected);

    try
    {
        throw_short();
    }
    catch (short)
    {
        // Everything is OK!
    }
}
