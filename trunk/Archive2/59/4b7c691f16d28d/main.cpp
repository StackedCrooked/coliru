struct foo {
    int i;
};

struct bar {
    int foo::*ptm = &foo::i;
};

struct baz {
    int foo::*bar::*ptm = &bar::ptm;
};

int main()
{
    foo f { 42 };
    bar b;
    baz c;
    return f.*(b.*(c.ptm));
}