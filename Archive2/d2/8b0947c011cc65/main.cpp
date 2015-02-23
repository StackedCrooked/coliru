#include <iostream>
#include <sstream>
#include <vector>
#include <array>
 
int main()
{
    std::istringstream input("abc|def|gh");
    std::vector<std::array<char, 4>> v;
 
    // note: the following loop terminates when std::ios_base::operator bool()
    // on the stream returned from getline() returns false
    for (std::array<char, 4> a; input.getline(&a[0], 4, '|'); ) {
        v.push_back(a);
    }
 
    for (auto& a : v) {
        std::cout << &a[0] << '\n';
    }
}