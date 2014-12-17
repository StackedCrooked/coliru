#include <iostream>
#include <functional>

// definition
struct Foo
{
    std::reference_wrapper<std::ostream> stream;
};

// instantiations
Foo foos[] = {
    { std::cout },  
};

int main()
{
    // rebind?
    foos[0].stream = std::cref(std::cerr);
}
