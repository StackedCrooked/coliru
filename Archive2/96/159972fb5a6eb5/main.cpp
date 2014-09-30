struct B {};

struct A
{
    explicit A(const B&) {}
};

int main()
{
    B b;
    A a1(b);
    A a2 = b;
}
