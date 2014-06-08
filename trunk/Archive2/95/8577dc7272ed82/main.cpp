struct A
{
    A(int i) {}
};

struct B
{
    B(A a) {}
};

int main()
{
    int i = 1;
    A a(1);
    B b(A(i));
    с(a);
    return 0;
}