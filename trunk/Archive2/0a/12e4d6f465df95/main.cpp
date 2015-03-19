#include <iostream>
#include <vector>

struct Foo {
    virtual void fizzbuzz() = 0;
};

struct Sub1 : public Foo {
    virtual void fizzbuzz() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

struct Sub2 : public Foo {
};

int main()
{
    std::vector<Foo *> v { new Sub1() };
    v[0]->fizzbuzz();
}
