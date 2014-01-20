#include <iostream>

template<typename Func>
auto wrapper(Func f) -> decltype(f())
{
    // some stuff
    auto result = f();
    // other stuff
    return result;
}

int blah()
{
    return 2; 
}

void foo()
{
    std::cout << "Bleh" << std::endl;
}

int main(int argc, char* argv[])
{
    std::cout << wrapper(blah) << std::endl;
    wrapper(foo);
    
    return 0;
}
