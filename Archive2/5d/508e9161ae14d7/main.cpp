template <class x> struct Foo
{
    int getX(x *p) { return(0); }
    enum E12 { a };
};

template <> int Foo<int>::getX(int*)
{
    return(-15);
}

template <> enum Foo<int>::E12
{
    a, b, c
};

int main() { }