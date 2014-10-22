#include <iostream>
#include <string>
 
struct S
{
    std::string i[2] = { "first", "second" };
};
     
int main() {
    S s;
    std::cout << s.i[0] << std::endl; // выводит "first"
    return 0;
}