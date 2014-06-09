#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//int values[8] = {1,2,3,4,5,6,7,8};

std::vector<char> o;

int main()
{
    o.push_back('a');
    const char* hello = "abcdefg";
    std::copy(hello,hello+sizeof(hello),o.begin() + o.size());
    
    for( auto a : o)
        std::cout << a << std::endl;

}
