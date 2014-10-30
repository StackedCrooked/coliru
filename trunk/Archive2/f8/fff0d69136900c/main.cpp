#include <iostream>
#include <cstring>
 
int main()
{
    char source[] = "areyou compiling me????...";
    char dest[4];
 
    std::memcpy(dest, source, sizeof dest);
 
    for (char c : dest) {
        std::cout << c << '\n';
    }
}