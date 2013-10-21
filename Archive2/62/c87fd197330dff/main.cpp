#include <iostream>
#include <sstream>
 
int main()
{
    std::stringstream stream("Hello, world");
    std::cout << "sgetc() returned '" << (char)stream.rdbuf()->sgetc() << "'\n"
              << "peek() returned '" << (char)stream.peek() << "'\n"
              << "get() returned '" << (char)stream.get() << "'\n";
}
