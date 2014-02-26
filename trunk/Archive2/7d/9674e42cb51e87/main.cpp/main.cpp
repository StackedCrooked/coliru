#include <ctime>
#include <iostream>
#include <locale>
 
int main()
{
    std::time_t t = std::time(NULL);
    char mbstr[100];
    if (std::strftime(mbstr, 100, "13%y%m%d%H%2M%S", std::localtime(&t))) {
        std::cout << mbstr << '\n';
    }
}