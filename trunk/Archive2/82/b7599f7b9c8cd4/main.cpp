#include <iostream>
class mystreambuf : public std::streambuf
{
};

int main()
{
mystreambuf* buf = (mystreambuf*)std::cout.rdbuf(); std::cout.rdbuf(buf);
std::cout << "Hi.\n";
}