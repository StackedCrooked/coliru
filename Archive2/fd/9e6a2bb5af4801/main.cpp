struct Derived;

struct Base
{
    Base() = default;
    Base(int p) : m(p) {}
    
    void bar(Derived&);
protected:
    int m;
};

struct Derived : Base
{
    Derived(Base const& p, int) : Base(p) {}
    void foo(Derived& p) { p.m = 42; } // allowed
    //void foo(Base& p) { p.m = 42; } // not allowed
    //void foo(Base  p) { p.m = 42; } // not allowed
};

void Base::bar(Derived& p)
{
    p.m = 42; // allowed
}

int main()
{
    Base b;
    Derived d0(b, 42);
    
    Derived d(b, 42);
    d.foo(d0);
}