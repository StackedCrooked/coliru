#include <iostream>
#include <sstream>

int main()
{
    std::stringstream ss;
    char buf[5] = {};

    ss.rdbuf()->pubsetbuf(buf, sizeof buf);
    ss.rdbuf()->sputn("hello world", 12);

    std::cout << ss.rdbuf(); // prints "Hello world"
    std::cout << buf[0];
}