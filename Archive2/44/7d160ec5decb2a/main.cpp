#include <iostream>
#include <utility>    // for std::move

#include <cstdlib>

class A
{
public:
    A() : value_()
        { std::cout << "A defualt constructor. (" << this << ')' << std::endl; }
    A(int value) : value_(value)
        { std::cout << "A constructor. (" << this << ')' << std::endl; }
    A(const A& rsh) : value_(rsh.value_)
        { std::cout << "A copy constructor. (" << this << ')' << std::endl; }
    A(A&& rsh) : value_(rsh.value_)
        { std::cout << "A move constructor. (" << this << ')' << std::endl;}
    ~A()
        { std::cout << "A destructor. (" << this << ')' << std::endl; }

    friend A operator+(const A& lsh, const A& rsh)
    {
        std::cout << "in friend A operator+(const A& lsh, const A& rsh)"
            << std::endl;
        return A(lsh.value_ + rsh.value_);
    }

    friend A&& operator+(A&& lsh, const A& rsh)
    {
        std::cout << "in friend A&& operator+(A&& lsh, const A& rsh), &lsh = ["
            << &lsh << ']' << std::endl;
        lsh.value_ += rsh.value_;
        return std::move(lsh);
    }

    friend A&& operator+(A&& lsh, A&& rsh)
    {
        std::cout << "in friend A&& operator+(A&& lsh, A&& rsh), &lsh = ["
            << &lsh << ']' << std::endl;
        lsh.value_ += rsh.value_;
        return std::move(lsh);
    }

    int value() const { return value_; }
    void value(int value) { value_ = value; }

private:
    int value_;
};

int main()
{
    std::cout << "A a1(68);" << std::endl;
    A a1(68);

    std::cout << "A a2(a1 + 100);" << std::endl;
    A a2(a1 + 100);

    std::cout << "A a3((a1 + a2) + 500);" << std::endl;
    A a3((a1 + a2) + 500);

    std::cout << "A a4(a1 + a2 + a3);" << std::endl;
    A a4(a1 + a2 + a3);

    std::cout << "A a5(a1 + a2 + a3 + a4);" << std::endl;
    A a5(a1 + a2 + a3 + a4);

    std::cout << "A a6(std::move(a1));" << std::endl;
    A a6(std::move(a1));

    std::cout << std::endl;

    return EXIT_SUCCESS;
}
