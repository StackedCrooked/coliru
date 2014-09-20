#include <iostream>
#include <memory>

struct Common {};

struct B;
struct A : public Common
{
    std::shared_ptr<Common> _a;
    A() : _a(this){ std::cout << this << ": A()\n"; }
    ~A() { std::cout << this << ": ~A(), _a -> " << _a.get() << '\n'; }

    void rebind(const std::shared_ptr<Common>& c)
    {
        std::cout << this << ": rebind from " << _a.get() << " to " << c.get() << '\n';
        _a = c;
        std::cout << this << ": rebind complete.\n";
    }
};

struct B : public Common
{
    std::shared_ptr<Common> _b;
    B() : _b(this) { std::cout << this << ": B()\n"; }
    ~B() { std::cout << this << ": ~B(), _b -> " << _b.get() << '\n'; }

    void rebind(const std::shared_ptr<Common>& c)
    {
        std::cout << this << ": rebind from " << _b.get() << " to " << c.get() << '\n';
        _b = c;
        std::cout << this << ": rebind complete.\n";
    }
};

struct scope_guard
{
    scope_guard() { std::cout << "Scope entered\n"; }
    ~scope_guard() { std::cout << "Scope exited\n"; }
};


int main() 
{
    {
        scope_guard guard;

        A* a = new A;
        std::shared_ptr<B> b(new B);

        a->rebind(b);
    }

    {
        scope_guard guard;

        A* a = new A;
        std::shared_ptr<B> b(new B);

        b->rebind(std::shared_ptr<Common>(a));
    }
}
