class Base
{
public:
    Base() = default;    
protected:
    ~Base() = default;
};

class Derived
:
    public Base
{  
    using Base::Base;
};

int main()
{
    Derived d1;
    Derived d2;
    d1 = d2;
}