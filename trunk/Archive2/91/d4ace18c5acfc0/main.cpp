#include <iostream>
#include <cstring>

int main()
{
    char buffer[20];
    buffer[9] = '\0';
    std::cout << strlen(buffer); 
}
