
struct Resolve
{
};

template<typename... Args>
struct Helper;
template<typename ResolverT, typename... Args>
struct Helper<Resolve, ResolverT, Args...>
: ResolverT::template Inheriter_t<Args...>
{
};
template<typename... Args>
struct Helper
: virtual Args...
{
};

template<typename DerivedT, typename... ParentT>
struct Middle
: Helper<ParentT...>
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

struct ABResolver
{
    template<typename... Args>
    struct Inheriter_t
    : virtual Args...
    {
        virtual Inheriter_t *f() const override = 0;
    };
};

struct Derived
: Middle<Derived, Resolve, ABResolver, A, B>
{
    virtual Derived *f() const override = 0;
};

int main()
{
}
