#include <vector>
#include <iostream>
 
int main()
{
    std::vector<char> letters {'A', 'm', 'g', 'w', 't', 'f'};
 
    if (!letters.empty()) {
        std::cout << "The first character is: " << letters.front() << '\n';
    }  
}