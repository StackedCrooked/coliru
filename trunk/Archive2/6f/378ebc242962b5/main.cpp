template <class>
class A
{
    void f() const {}
};

template <class T>
struct B : A<T>
{
    template <class U>
    friend void g(B<U> const& b);
};

template <class U>
void g(B<U> const& b)
{
    b.f();
}
    
int main()
{
}