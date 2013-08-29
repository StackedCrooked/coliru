class A{};
class B : private A
{
    void foo()
    {
        auto x = static_cast<A&>(*this);
    }
};

int main()
{
}
