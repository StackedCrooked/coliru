#include <sstream>
#include <iostream>

int main()
{
    std::ostringstream ss;
    ss << "lolol" << std::flush;
    
    std::cout << ss.rdbuf() << '\n';
    const bool is_failed = std::cout.fail();
    
    std::cout.clear();
    std::cout << is_failed << '\n';
}
