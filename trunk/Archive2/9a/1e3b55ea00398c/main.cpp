#include <iostream>
#include <algorithm>
#include <string>
 
void test(const std::string& s)
{
    if(std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin())) {
        std::cout << "\"" << s << "\" - палиндром\n";
    } else {
        std::cout << "\"" << s << "\" не палиндром\n";
    }
}
int main()
{
    test("радар");
    test("привет");
}