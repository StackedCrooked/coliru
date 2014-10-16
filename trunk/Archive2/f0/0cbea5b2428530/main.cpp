using T = void(int) const;
using U = void(double) const;

struct Foo
{
    virtual T x;
    virtual U x;
};

void Foo::x(int) const
{
}

void Foo::x(double) const
{
}

int main()
{
    Foo x;
}