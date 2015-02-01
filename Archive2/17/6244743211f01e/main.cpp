struct X{};

struct Y : X
{
    using X::X;
};

void foo(Y const&){}

int main()
{
    X x;
    foo(x);
}