#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
    char* words[] = {"Hello", "from", "GCC", __VERSION__, "!"};
    
    std::copy(words, words+5, std::ostream_iterator<char*>(std::cout, " "));
}
