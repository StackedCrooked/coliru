#include <memory>
#include <iostream>

template<typename T, typename stream = std::ostream>
class foo
{
public:
//member definition
    void print(stream& f);
};

template<typename T, typename stream = std::ostream>
void foo::print(stream& f) {
    f  << "Hi";
};

int main()
{
    
    foo<int> f;
    f.print(std::cout);
}