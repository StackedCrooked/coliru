#include <iostream>
#include <string>
#include <vector>


struct E_impl{};
constexpr E_impl E;

struct multiplicative_type{
    double val_ = 0;
    multiplicative_type(double val = 0) : val_(val) {}
    friend multiplicative_type operator+(E_impl e, multiplicative_type val);
    
};

multiplicative_type operator+(E_impl e, multiplicative_type val)
{
    return multiplicative_type();
}

int main()
{
    std::cout << "test" << std::endl;
}
