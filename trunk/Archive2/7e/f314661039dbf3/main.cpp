#include <iostream>
#include <string>

struct Type
{
    std::string s;
    Type()
    {
        std::cout << "default ctor" << std::endl;
    }
    Type(std::string const &s)
    : s(s)
    {
        std::cout << "string ctor \"" << s << '"' << std::endl;
    }
    Type(Type const &from)
    : s(from.s)
    {
        std::cout << "copy ctor \"" << s << '"' << std::endl;
    }
    Type &operator=(Type const &from)
    {
        s = from.s;
        std::cout << "copy assign \"" << s << '"' << std::endl;
        return *this;
    }
    Type(Type &&from)
    : s(std::move(from.s))
    {
        std::cout << "move ctor \"" << s << '"' << std::endl;
    }
    Type &operator=(Type &&from)
    {
        s = std::move(from.s);
        std::cout << "move assign \"" << s << '"' << std::endl;
        return *this;
    }
};

struct Test
{
    Type t;

    auto stealA()
    -> Type
    {
        return std::move(t);
    }
    auto stealB()
    -> Type &&
    {
        return std::move(t);
    }
};

int main()
{
    Test t1 {{"A"}};
    auto a = t1.stealA();
    std::cout << a.s << std::endl;

    Test t2 {{"B"}};
    auto b = t2.stealB();
    std::cout << b.s << std::endl;
}
