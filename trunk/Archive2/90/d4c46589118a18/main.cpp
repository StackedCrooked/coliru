#include <iostream>
#include <iterator>
#include <string>


int main() 
{
    std::ostream_iterator<std::string> it(std::cout);
    it = "Happy New Year";
}