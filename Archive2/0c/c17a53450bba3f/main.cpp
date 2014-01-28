#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::vector<const std::string> test({"Hello", "From", "C++11"});
    std::cout << test.size() << std::endl;
}
