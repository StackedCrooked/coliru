#include <iostream>
#include <vector>
#include <string>

template<typename T>
void destroy(T *p)
{
    p->~T();
}

int main()
{
    //std::vector<const std::string> test;
    //std::cout << test.size() << std::endl;
    
    const std::string x[] = {
        "hello"
    };
    
    destroy(x);
}
