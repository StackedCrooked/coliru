#include <iostream>
#include <sstream>
 
int main()
{
    char c[10] = {};
    std::istringstream input("This is sample text."); // std::stringbuf makes its entire
                                                      // buffer available for unblocking read
    input.readsome(c, 5); // reads 'This ' and stores in c[0] .. c[4]
    input.readsome(c, 9); // reads 'is sample' and stores in c[0] .. c[8]
    std::cout << c;
}