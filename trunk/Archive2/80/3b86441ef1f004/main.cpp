#include <iostream>


int main()
{
    try
    {
        throw "1";
    }
    catch (decltype("1"))
    {
        std::cout << __LINE__ << std::endl;
    }
    catch (const char*)
    {
        std::cout << __LINE__ << std::endl;
    }
}
