#include <iostream>
#include <cstdlib>
 
int main()
{
    const char* begin = "10 20 30 40";
    char *end;
    for (unsigned long i = std::strtoul(begin, &end, 10);
         begin != end;
         i = std::strtoul(begin, &end, 10))
    {
        begin = end;
        if (errno == ERANGE)
            std::cout << "range error" << std::endl;
        std::cout << i << '\n';
    }
}