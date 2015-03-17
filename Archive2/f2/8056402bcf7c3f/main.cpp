#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

int main()
{
    std::wcout << boost::lexical_cast<std::wstring>(2147483647);
    return 0;
}