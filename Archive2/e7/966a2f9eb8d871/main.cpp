
struct A
{
    A() = default;
    explicit A(const A& a) = default;
};
A f()
{
    return {};
}
int main()
{
    A a;
    A b(a);
    
}