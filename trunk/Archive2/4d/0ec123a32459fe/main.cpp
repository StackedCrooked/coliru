#include <iostream>
#include <cstdlib>
 
int main()
{
    const char* begin = "10 20000000000000000000000 30 40";
    char *end;
    for (long i = std::strtol(begin, &end, 10);
         begin != end;
         i = std::strtol(begin, &end, 10))
    {
        begin = end;
        if (errno == ERANGE){
            std::cout << "range error\n";
            errno = 0;
        }     
        std::cout << i << '\n';
    }
}