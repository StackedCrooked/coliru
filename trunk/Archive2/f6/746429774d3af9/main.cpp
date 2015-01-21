    class A
    {
    public:
    void f() const& {}
    };
     
    int main()
    {
    const A a = A();
    a.f();
    }