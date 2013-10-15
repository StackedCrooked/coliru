struct Base
{
protected:
    int m;
};

struct Derived : Base
{
    void foo(Derived& p) { p.m = 42; } // allowed
    //void foo(Base& p) { p.m = 42; } // not allowed
    //void foo(Base  p) { p.m = 42; } // not allowed
};

int main()
{
    Derived d0;
    
    Derived d;
    d.foo(d0);
}