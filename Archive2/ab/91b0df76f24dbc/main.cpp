struct Base
{
    virtual ~Base() = default;

    virtual Base *f() const = 0;
};

struct A
: virtual Base
{
    virtual A *f() const override = 0;
};
struct B
: virtual Base
{
    virtual B *f() const override = 0;
};

struct dummy
: virtual A
, virtual B
{
    dummy* f() const override = 0;
};

struct Middle
: dummy
{
    
};

struct Derived
: Middle
{
    virtual Derived *f() const override = 0;
};


int main()
{
}
