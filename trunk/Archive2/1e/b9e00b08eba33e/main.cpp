#include <vector>
#include <iostream>
 
int main()
{
    std::vector<char> characters;
 
    characters.assign(5, 'b');
 
    for (char c : characters) {
        std::cout << c << '\n';
    } 
 
    return 0;
}