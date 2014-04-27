#include <iostream>
#include <string>
 
int main()
{
    std::string str("The quick brown fox jumps over the lazy dog.");
 
    str.replace(10, 5, "red"); // (4)
 
    str.replace(str.begin(), str.begin() + 3, 1, 'A'); // (5)
 
    std::cout << str << '\n';
}