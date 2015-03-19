#include <iostream>
#include <vector>

struct Foo {
    virtual void fizzbuzz() {}
};

struct Sub1 : public Foo {
    virtual void fizzbuzz() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

struct Sub2 : public Foo {
    virtual void fizzbuzz() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

int main()
{
    std::vector<Foo *> v { new Sub1(), new Sub2() };
    v[0]->fizzbuzz();
    v[1]->fizzbuzz();
}
