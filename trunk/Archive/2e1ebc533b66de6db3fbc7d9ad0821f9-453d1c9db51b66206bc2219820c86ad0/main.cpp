#include <memory>
#include <iostream>

template<typename T>
class foo
{
public:
//member definition
    template<typename U, typename F = std::ostream> class X 
    {
    typedef F stream; //How???
    public:
        void print(stream &f) { f  << "Hi"; }
    };
};

int main()
{
    
    foo<int>::X<int> f;
    f.print(std::cout);
}