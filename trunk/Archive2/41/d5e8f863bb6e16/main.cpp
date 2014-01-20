template <typename T>
struct Base
{
    Base(int x) {}
};

struct Derived1 : Base<Derived1>
{
    Derived1() : Base(2) {}
};

int main() {}