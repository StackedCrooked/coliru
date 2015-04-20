
struct A
{
    int f() { return 42; }
    const int g() const { return 43; }
};

int main()
{
    A a;
    const A ca;
    a.f() = 1;
    ca.g() = 2;
}
