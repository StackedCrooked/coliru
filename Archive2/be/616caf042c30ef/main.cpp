#include <iostream>
#include <ctime>
#include <string>

std::string now()
{
    std::time_t curr = std::time(nullptr);
    char cstr[128] ;

    // http://en.cppreference.com/w/cpp/chrono/c/strftime
    std::strftime( cstr, sizeof(cstr), "%Y%m%d%H%M%S", std::gmtime(&curr) ) ;

    return cstr ;
}

int main()
{
    std::cout << "utc: " + now() << '\n' ;
}
