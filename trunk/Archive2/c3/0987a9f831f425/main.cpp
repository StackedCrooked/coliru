#include <ctime>
#include <iostream>
#include <locale>
 
int main()
{
    std::time_t t = std::time(NULL);
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %H:%M:%S", std::localtime(&t))) {
        std::cout << mbstr << '\n';
    }
}