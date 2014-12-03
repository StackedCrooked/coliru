#include <utility>

template<class T, void (T::*f)()&>
class B
{
public:
    void g(int) noexcept(noexcept((std::declval<T&>().*f)()))  // declval<T> will not compile
    {}
    
    B(T& x) : x(x) {}
private:
    T& x;
};

struct foo
{
    void bar()& {}
};

int main()
{
    foo f;
    B<foo, &foo::bar> b(f);
    b.g(42);
}
