#include <fstream>
#include <iostream>
 
int main()
{
    std::cout.put('a'); // normal usage
    std::cout.put('\n');
 
    std::ofstream s("/does/not/exist/");
    s.clear(); // pretend the stream is good
    std::cout << "Unformatted output: ";
    s.put('c'); // this will set badbit, but not failbit
    std::cout << " fail=" << bool(s.rdstate() & s.failbit);
    std::cout << " bad=" << s.bad() << '\n';
    s.clear();
    std::cout << "Formatted output:   ";
    s << 'c'; // this will set badbit and failbit
    std::cout << " fail=" << bool(s.rdstate() & s.failbit);
    std::cout << " bad=" << s.bad() << '\n';
}