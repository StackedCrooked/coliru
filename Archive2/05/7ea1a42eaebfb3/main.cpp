
template<typename DerivedT, typename... ParentT>
struct Middle
: virtual ParentT...
{
};

struct Base
: Middle<Base>
{
    virtual ~Base() = default;

    virtual Base *f() const = 0;
};

struct A
: Middle<A, Base>
{
    virtual A *f() const override = 0;
};
struct B
: Middle<B, Base>
{
    virtual B *f() const override = 0;
};

struct Derived
: Middle<Derived, A, B>
{
    virtual Derived *f() const override = 0;
};

int main()
{
}
