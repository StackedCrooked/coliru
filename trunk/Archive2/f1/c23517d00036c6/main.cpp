struct Base 
{
    virtual ~Base() = default;

    virtual Base *f() const = 0;
};

struct A : virtual Base
{
    virtual A *f() const override = 0;
};

struct B : virtual Base
{
    virtual B *f() const override = 0;
};

struct Middle : virtual A, virtual B
{
};
