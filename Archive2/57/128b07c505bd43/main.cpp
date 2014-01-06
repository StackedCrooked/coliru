
struct A
{
};

struct B : A
{
    using A::A;
};

int main()
{
    A a;
    B b (a);
}
