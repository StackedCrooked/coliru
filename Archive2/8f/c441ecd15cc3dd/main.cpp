#include <iostream>
#include <fstream>
 
int main()
{
    std::ofstream out;
 
    out.copyfmt(std::cout); // copy everything except rdstate and rdbuf
    out.clear(std::cout.rdstate()); // copy rdstate
    out.basic_ios<char>::rdbuf(std::cout.rdbuf()); // share the buffer
 
    out << "Hello, world\n";
}