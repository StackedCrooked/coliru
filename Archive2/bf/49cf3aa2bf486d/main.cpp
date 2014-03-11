#include <iostream>

int main()
{
    char const *s = "Hello, world!"; 
    char *s2 = const_cast<char *>(s); //bad
    std::cout << s2 << std::endl; //fine, but scary
    s2[0] = 'h'; //undefined behavior, anything could happen
    std::cout << s2 << std::endl; //assuming the program is still running, what does this print?
    std::cout << s << std::endl; //assuming the program is still running, what does this print?
}
