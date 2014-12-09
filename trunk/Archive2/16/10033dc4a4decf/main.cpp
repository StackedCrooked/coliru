#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

int main()
{
    std::stringbuf sb("hellohellohello");

    for (int i = 0; i < 3; ++i) {
        std::string hello;
        
        std::copy_n(std::istreambuf_iterator<char>(&sb),
                    5,
                    std::back_inserter(hello));
                    
        sb.pubseekoff(i * 5, std::ios_base::beg);
                    
        std::cout << hello << std::endl;
    }
}