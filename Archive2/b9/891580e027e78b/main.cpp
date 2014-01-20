#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
 
int main()
{
    std::string in = "1234567890";
    std::string out;
 
    std::copy_n(in.begin(), 4, std::back_inserter(out));
    std::cout << out << '\n';
}