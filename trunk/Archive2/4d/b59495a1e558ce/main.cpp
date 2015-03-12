#include <iostream>
#include <list>

class holder
{
public:
    holder& operator<<(int v)
    {
        integers.push_back(v);
        return *this;
    }
    
    holder& operator<<(double v)
    {
        doubles.push_back(v);
        return *this;
    }
    
    std::list<int> integers;
    std::list<double> doubles;
};

class printer
{
public:
    void print(const holder& h)
    {
        std::cout << "integers: " << std::endl;
        for (auto v : h.integers)
        {
            std::cout << v << std::endl;   
        }
        std::cout << "doubles: " << std::endl;
        for (auto v : h.doubles)
        {
            std::cout << v << std::endl;   
        }
    }
};

int main(int argc, char* argv[])
{
    printer p;
    p.print(holder() << 1 << 2.666 << 3 << 8.6);
    
    return 0;
}
