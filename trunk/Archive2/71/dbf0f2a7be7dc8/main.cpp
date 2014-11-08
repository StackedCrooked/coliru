#include <iostream>

struct B;

struct A
{
    B* b;
    void linkWith(B& b);
    void unlink();
};

struct B
{
    A* a;
};

void A::linkWith(B& b)
{
    this->b = &b;
    b.a = this;
}

void A::unlink()
{
    b->a = nullptr;
    b = nullptr;
}

void modifyConstObject(const B& b)
{
    std::cout << "Before: " << b.a << "\n";
    b.a->unlink();
    std::cout << "After: " << b.a << std::endl; // WTF?
}

int main()
{
    A a;
    B b;
    a.linkWith(b);
    modifyConstObject(b);
}