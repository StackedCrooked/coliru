#include <iostream>
#include <string>
#include <set>
#include <tuple>
 
int main()
{
    std::set<std::string> set_of_str;
    bool inserted;
    std::tie(std::ignore, inserted) = set_of_str.insert("Test");
    if (inserted) {
        std::cout << "Value was inserted sucessfully\n";
    }
}