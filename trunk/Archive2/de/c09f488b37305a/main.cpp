
struct Base
{
    virtual ~Base() = default;

    virtual Base *f() const = 0;
};

struct A
: virtual Base
{
    virtual Base *f() const override = 0;
};
struct B
: virtual Base
{
    virtual Base *f() const override = 0;
};

struct Middle
: virtual A
, virtual B
{
};

struct Derived
: Middle
{
    virtual Base *f() const override = 0;
};

int main()
{
}
