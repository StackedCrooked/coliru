#include <string>

class Base1
{
    public:

    void operator [] (const std::string& s) { }
};

class Base2
{
    public:

    void operator [] (std::size_t idx) { }
};

class Derived : public Base1, public Base2
{
    public:
    using Base1::operator[];
    using Base2::operator[];
};

int main()
{
    Derived d;
    d[0];
}