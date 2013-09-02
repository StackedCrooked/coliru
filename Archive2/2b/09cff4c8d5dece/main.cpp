namespace bar
{
struct B {};
void size( B ) {}
}

struct A
{
    void size() const {}
    void foo()
    {
        using bar::size;
        bar::B b;
        return size( b );
    }
};

auto main() -> int {}
