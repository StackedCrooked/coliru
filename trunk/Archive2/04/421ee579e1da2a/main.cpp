struct A {};
struct B {};

B foo()
{
    A a;
    B b;
    return a = A(), b;
}

int main()
{
    foo();
}