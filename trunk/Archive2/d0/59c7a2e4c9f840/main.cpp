#include <iostream>
#include <thread>

class parallel_cout : public std::ostream
{
public:
    parallel_cout(std::ostream& o) : out(o) {}

    template <typename T>
    std::ostream& operator<<(const T& val)
    {
        out << "prefix " << val;
        return *this;
    }
    
    std::ostream& out;
};

int main()
{
    parallel_cout pc(std::cout);
    pc << "a\nb" << "c\n";
}