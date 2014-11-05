#include <memory>
#include <iostream>

using namespace std;

struct Noisy
{
    Noisy() { std::cout << "Noisy()" << std::endl; }
    Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)" << std::endl; }
    Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)" << std::endl; }
    ~Noisy() { std::cout << "~Noisy()" << std::endl; }
    Noisy& operator=(const Noisy&) { std::cout << "operator=(const Noisy&)" << std::endl; return *this; }
    Noisy& operator=(Noisy&&) { std::cout << "operator=(Noisy&&)" << std::endl; return *this; }
};

int main()
{
    {
        auto buf1 = unique_ptr<Noisy[]>(new Noisy[3]);
    }
    
    std::cout << std::endl;
    
    {
        auto buf2 = make_unique<Noisy[]>(3);
    }
    
    std::cout << std::endl;
    
    // WARNING: invalid code below:!
    {
        auto buf3 = unique_ptr<Noisy>(new Noisy[3]);
    }
}
