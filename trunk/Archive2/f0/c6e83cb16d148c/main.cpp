class Base
{
protected:
    Base(int, int, int, int);

public:
    virtual void SomeMethod() = 0;
};

class Derived : public Base
{
public:
    using Base::Base;

public:
    virtual void SomeMethod() override;
};


int main() {}