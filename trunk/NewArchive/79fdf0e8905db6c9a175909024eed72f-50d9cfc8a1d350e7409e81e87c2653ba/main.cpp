#include <memory>
#include <iostream>


void foo(int)
{
    std::cerr << "I pity the foo!" << std::endl;
}


#define foo(...) [](){ \
        std::cout << "BEFORE FOO" << std::endl; \
        std::shared_ptr<void> ptr(nullptr, [](void*){ std::cout << "AFTER FOO" << std::endl; }); \
        return foo(__VA_ARGS__); \
    }()


int main()
{
    foo(0);
}