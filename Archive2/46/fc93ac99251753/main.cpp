#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

bool string_in_vector(const std::string &str,std::vector<std::string> &arr)
{
 return std::find(std::begin(arr),std::end(arr),str) != std::end(arr);
}

int main()
{
    std::string s = "foo";
    std::vector<std::string> vec = { "foo", "bar", "baz" };
    std::cout << std::boolalpha << string_in_vector(s, vec);
    return 0;
}