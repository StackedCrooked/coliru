#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class A
{
public:
    void print_a()
    {
        std::cout << "A" << std::endl;
    }
};

class B
{
public:
    void print_b()
    {
        std::cout << "B" << std::endl;
    }
};



int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    A* a = new A();
    a->print_a();
    
    B& b = (B&)(a);
    b.print_b();
    
    //B* b = static_cast<B*>(a);
    //b->print_b();
}
