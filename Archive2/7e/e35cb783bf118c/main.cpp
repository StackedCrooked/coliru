template<typename T> struct Impl;
template<typename T> struct Nested;

template <typename T>
class Base
{
private:
    typename Nested<T>::type c;
};

struct A;

template<> struct Impl<A>   { class B { }; };
template<> struct Nested<A> { using type = typename Impl<A>::B; };

struct A : Base<A>, Impl<A>
{
    //...
};

int main ()
{
  A a;
}