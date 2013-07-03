#include <iostream>
#include <sstream>

int main()
{
    std::stringstream ss;
    char buf[5] = {};
    char buf1[20] = "ABCDEF";

    ss.rdbuf()->pubsetbuf(buf, sizeof buf);
    ss.rdbuf()->sputn("hello world", 12);

    std::cout << ss.rdbuf(); // prints "Hello world"
    std::cout << buf[0];
    std::cout << buf1[0] <<  buf1[2];
}