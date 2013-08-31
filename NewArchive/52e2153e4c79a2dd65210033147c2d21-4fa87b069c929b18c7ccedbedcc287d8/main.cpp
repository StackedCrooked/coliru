struct A
{
    explicit A() = default;
    A(A const&) = default;
    A(A&&) = default;
};

int main()
{
    A a = A();
}
