#include <iostream>
#include <string>
#include <vector>

template<typename F, typename ...Args>
void process(F const& first)
{
    std::cout << sizeof(F) << std::endl;
}

template<typename F, typename ...Args>
void process(F const& first, Args const& ...args)
{
    process(first);
    process(args...);
}

template<typename T, typename ...Args>
bool lookup(T*& p, Args const& ...args)
{
    std::cout << "Processing..." << std::endl;
    process(args...);
    return true;
}

class C
{
        
};

int main()
{
    C* p = nullptr;
    lookup(p, char(1), short(2), int(3), long(4), float(5), double(6));
}
