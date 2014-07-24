#include <iostream>
#include <utility>

struct loud
{
    loud() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    loud(loud const&) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    loud(loud&&) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    loud& operator=(loud const&) { std::cout << __PRETTY_FUNCTION__ << "\n"; return *this; }
    loud& operator=(loud&&) { std::cout << __PRETTY_FUNCTION__ << "\n"; return *this; }
    ~loud() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};


struct foo
{
    loud l;
    virtual ~foo() {}
};

struct bar
{
    loud l;
    virtual ~bar() = default;
};

struct make_polymorphic
{
    virtual ~make_polymorphic() = default;
};

struct meow : make_polymorphic
{
    loud l;
};

int main()
{
    foo f;
    bar b;
    meow m;
    
    auto x = std::move(f);
    auto y = std::move(b);
    auto z = std::move(m);
}