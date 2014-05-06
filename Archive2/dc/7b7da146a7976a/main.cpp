#include <iostream>
#include <memory>

struct X
{
    ~X() { std::cout << "Destruction!" << std::endl; }
};

int main()
{
    std::shared_ptr<X> x{new X{}};
    {
        auto x1 = x;
    }
    
    std::cout << "Bye bye..." << std::endl;
}
