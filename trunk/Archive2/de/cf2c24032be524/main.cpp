#include <stdexcept>
#include <iostream>

struct X : virtual std::exception { };

int main()
{
    try
    {
        throw X{};
    }
    catch (std::exception const&)
    {
        std::cout << "Caught std::exception" << std::endl;
    }
    catch (X const&)
    {
        std::cout << "Caught X" << std::endl;
    }
}