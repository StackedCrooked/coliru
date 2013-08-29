#include <memory>
#include <iostream>


void foo(int n)
{
    std::cerr << "I pity the foo!" << std::endl;
}


#define foo(...) [](){ \
        std::cout << __FILE__ << ":" << __LINE__ << ": calling foo..." << std::flush; \
        std::shared_ptr<void> ptr(nullptr, [](void*){ std::cout << " Done!" << std::endl; }); \
        return foo(__VA_ARGS__); \
    }()


int main()
{
    foo(3);
    foo(4);
}