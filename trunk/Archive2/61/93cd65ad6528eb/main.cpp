template <typename T>
struct Base
{
    Base(int x) {}
};

struct Derived : Base<int>
{
    Derived() : Base(2) {}
};

int main()
{
        Derived d;
}
