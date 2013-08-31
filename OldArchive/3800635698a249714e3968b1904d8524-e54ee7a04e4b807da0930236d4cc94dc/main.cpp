#include <iostream>
#include <string>


template<typename F>
void helper(unsigned n, char& end, F&& f)
{
    char begin = 0;
    auto distance = (reinterpret_cast<uint64_t>(&end) - reinterpret_cast<uint64_t>(&begin));
    
    if (distance > n)
    {        
        f(&begin, &end - (distance - n));
        return;
    }
    
    helper(n, end, std::forward<F>(f));
}


template<typename F>
void dynalloc(unsigned n, F&& f)
{
    char end = 0; // stack grows downwards
    helper(n, end, f);
}


int main()
{
    dynalloc(1000, [](char* begin, char* end) {
        std::cout << "I have allocated " << (end - begin) << " bytes on the stack." << std::endl;
    });
}
