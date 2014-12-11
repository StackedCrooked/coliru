#include <iostream>
#include <string>
#include <vector>

class B
{
public:
    bool operator<(B const& r) const
    {
        std::cout << "Called" << std::endl;
        return true;
    }
};

class D : public B
{
public:
};


int main()
{
    D a, b;
    std::cout << (a < b) << std::endl;
}
