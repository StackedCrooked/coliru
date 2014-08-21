#include <sstream>
#include <iostream>
 
int main()
{
    std::istringstream s1("Hello, world.");
    char c1 = s1.get(); // reads 'H'
    std::cout << "after reading " << c1 << ", gcount() == " <<  s1.gcount() << '\n';
    char c2;
    s1.get(c2);         // reads 'e'
    char str[5];
    s1.get(str, 5);     // reads "llo,"
    std::cout << "after reading " << str << ", gcount() == " <<  s1.gcount() << '\n';
    std::cout << c1 << c2 << str;
    s1.get(*std::cout.rdbuf()); // reads the rest, not including '\n'
    std::cout << "\nAfter the last get(), gcount() == " << s1.gcount() << '\n';
}