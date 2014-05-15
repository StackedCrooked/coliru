#include <iostream>

class Base_t
{
private:
    struct Priv_t
    {
    } p;
    friend std::ostream & operator<<(std::ostream &os, const Base_t& obj);
    friend std::ostream & operator<<(std::ostream &os, const Base_t::Priv_t& obj);
};

std::ostream & operator<<(std::ostream &os, const Base_t& obj)
{
    return os << "base: " << obj.p;
}

std::ostream & operator<<(std::ostream &os, const Base_t::Priv_t& obj)
{
    return os << "priv";
}

int main()
{
    Base_t b;
    std::cout << b << std::endl;
}