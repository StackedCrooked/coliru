#include <iostream>
class mystreambuf : public std::streambuf
{
public:
    mystreambuf(const std::streambuf& other) : std::streambuf(other)
    {
    }
};

int main()
{
    mystreambuf buf(*std::cout.rdbuf());
    std::cout.rdbuf(&buf);
    
    std::cout << "Hello";
}