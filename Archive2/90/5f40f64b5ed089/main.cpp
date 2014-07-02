

void call_from_base();
void call_from_foo();

struct Base
{
    virtual void foo()
    {
        call_from_base();
    }
};

struct Derived : Base
{
    virtual void foo()
    {
        call_from_foo();
    }
};


Derived d = []{
    Derived d;
    d.foo();
    return d;
}();