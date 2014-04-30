#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>
int main()
{
    std::string str = "Text with some   spaces";
    std::cout << "before: " << str << "\n";
 
    std::cout << "after:  ";
    std::remove_copy(str.begin(), str.end(),
                     std::ostream_iterator<char>(std::cout), ' ');
    std::cout << '\n';
}