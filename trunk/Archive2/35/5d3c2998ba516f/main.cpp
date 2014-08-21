class Base
{
public:
    Base() = default;
    Base(const Base&) = default;
    Base(Base&&) = default;
    Base& operator=(const Base&) = default;
    Base& operator=(Base&&) = default;
protected:
    ~Base() = default;
};

class Derived
:
    public Base
{  
public:
    using Base::Base;
    Derived() = default;
    Derived(const Derived&) = default;
    Derived(Derived&&) = default;
    Derived& operator=(const Derived&) = default;
    Derived& operator=(Derived&&) = default;
};

int main()
{
    Derived d1;
    Derived d2;
    d1 = d2;
}