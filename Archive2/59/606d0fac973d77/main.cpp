struct A
{
    A(int a) {}
};

struct B : A
{
    using A::A; // Shorthand for B(int b) : A(b) {}?
};

int main()
{
    B b(3);
}