#include <iostream>
#include <string>

struct Type
{
    std::string s;
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
    Test t1 {{{"A"}}};
    auto a = t1.stealA();
    std::cout << a.s << std::endl;

    Test t2 {{{"B"}}};
    auto b = t2.stealB();
    std::cout << b.s << std::endl;
}
