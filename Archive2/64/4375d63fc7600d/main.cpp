class A
{
private:
    class B {};
};

template <typename>
using B = A::B;    // Expected error but compiles OK

int main()
{
    B<void> b;
}
