using T = void(int); using U = void(double);

struct Foo
{
    T x;
    U x;
};

void Foo::x(int)
{
}

void Foo::x(double)
{
}

int main()
{
    Foo x;
}