#include <iostream>
#include <sstream>
 
int main()
{
    // default constructor (mode = in|out)
    std::stringbuf buf1;
    buf1.sputc('1');
    std::cout << &buf1 << '\n';
 
    // string constructor in at-end mode (C++11)
    std::stringbuf buf2("test", std::ios_base::in
                              | std::ios_base::out
                              | std::ios_base::ate);
    buf2.sputc('1');
    std::cout << &buf2 << '\n';
 
    // append mode test (results differ among compilers)
    std::stringbuf buf3("test", std::ios_base::in
                              | std::ios_base::out
                              | std::ios_base::app);
    buf3.sputc('1');
    buf3.pubseekpos(1);
    buf3.sputc('2');
    std::cout << &buf3 << '\n';
}