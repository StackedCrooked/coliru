#include <iostream>
#include <memory>

struct X
{
    ~X() { std::cout << "Destruction!" << std::endl; }
};

int main()
{
    std::shared_ptr<X> x{new X{}};
    
    for (auto i = 0; i < 3; ++i)
    {
        auto x1 = x;
        // Possibly more stuff...
    }
    
    std::cout << "Bye bye..." << std::endl;
}
