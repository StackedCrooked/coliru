#include <iostream>
#include <sstream>
 
int main()
{
    std::stringstream s("abcdef"); // gptr() poitns to 'a'
    std::cout << "Before putback, string holds " << s.str() << '\n';
    char c1 = s.get(); // c = 'a', gptr() now points to 'b' 
    char c2 = s.rdbuf()->sputbackc('z'); // same as s.putback('c')
                                         // gptr() now points to 'z'
    std::cout << "After putback, string holds " << s.str() << '\n';
    char c3 = s.get(); // c3 = 'z', gptr() now points to 'b'
    char c4 = s.get(); // c4 = 'b', gptr() now points to 'c'
    std::cout << c1 << c2 << c3 << c4 << '\n';
 
    s.rdbuf()->sputbackc('b');  // back to 'b'
    s.rdbuf()->sputbackc('x');  // back to 'x'
    int eof = s.rdbuf()->sputbackc('x');  // nothing to unget: pbackfail() fails
    if (eof == EOF)
        std::cout << "No room to putback after 'z'\n";
    std::cout << "After putback, string holds " << s.str() << '\n';
}