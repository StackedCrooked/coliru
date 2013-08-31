#include <iostream>
#include <memory>

class Foo
{
public:
    virtual void print()
    {
        std::cout << "foo" << std::endl;
    }
};

class Bar: public Foo
{
public:
    void print()
    {
        std::cout << "bar" << std::endl;
    }
};

class Baz: public Bar
{
public:
    void print()
    {
        std::cout << "baz" << std::endl;
    }
};

int main()
{
    std::unique_ptr<Foo> f_ptr(new Baz);
    std::unique_ptr<Bar> b_ptr(new Baz);

    f_ptr -> print();
    b_ptr -> print();

    return 0;
}