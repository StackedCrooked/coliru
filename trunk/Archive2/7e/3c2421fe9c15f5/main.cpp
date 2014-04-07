#include <iostream>
#include <cstring>
 
int main()
{
    char source[] = "once upon a midnight dreary...";
    char dest[4];
    
    std::cout<<&source<<std::endl;
 
    std::memcpy(dest, source, sizeof dest);
 
    std::cout<<&dest<<std::endl;
    
    for (char c : dest) {
        std::cout << c << '\n';
    }
}