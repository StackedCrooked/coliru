#include <vector>
#include <iostream>
 
int main()
{
    std::vector<char> letters {'o', 'm', 'g', 'w', 't', 'f'};
 
    if (!letters.empty()) {
        std::cout << "The firracter is: " << letters.front() << '\n';
    }  
}