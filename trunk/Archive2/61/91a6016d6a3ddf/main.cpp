struct B;
struct A
{
    A();
    operator B();
};

struct B
{
    B(const A&);
};

int main()
{
    A a;
    (B)a;
}
