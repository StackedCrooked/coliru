#include <array>
#include <iostream>
 
int main()
{
    std::array<char> letters {'o', 'm', 'g', 'w', 't', 'f'};
 
    if (!letters.empty()) {
        std::cout << "The first character is: " << letters.front() << '\n';
    }  
}