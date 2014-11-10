#include <iostream>
#include <string>
void double_string(std::string& s)
{
    s += s; // 's' is the same object as main()'s 'str'
}
int main()
{
    std::string str = "Test";
    double_string(str);
    std::cout << str << '\n';
}