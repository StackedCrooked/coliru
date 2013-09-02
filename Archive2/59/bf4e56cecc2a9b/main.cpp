struct B {};
void size( B ) {}

struct A
{
    void size() const {}
    void foo()
    {
        B b;
        return size( b );   // No, not argument-dependent lookup here.
    }
};

auto main() -> int {}
