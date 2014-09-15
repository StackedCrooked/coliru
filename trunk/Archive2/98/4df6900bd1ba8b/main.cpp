class C
{
private:
    C() {}
public:
    C(int) {}
};

template<class T>
struct foo
{
    T t = {};
    
    foo(int p) : t(p) {}
    foo() {}
};

int main()
{
    foo<C> f{42};
}