#include <iostream>
#include <stdexcept>


void handle_unexpected()
{
    throw long();
}


int main()
{
    std::set_unexpected(handle_unexpected);

    try
    {
        throw short();
    }
    catch (long)
    {
    }
}
