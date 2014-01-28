#include <sstream>
#include <iostream>
 
int main()
{
    std::ostringstream os("hello, world");
    os.seekp(0);
    os << 'W';
    os.seekp(0, std::ios_base::end);
    os << '!';
    os.seekp(7);
    os << 'H';
    std::cout << os.str() << '\n';
}