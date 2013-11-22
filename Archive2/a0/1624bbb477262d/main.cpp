template <typename C>
struct A
{
    typedef C In;
    typedef C Out;
};
template <typename C>
A<C> make_a()
{
    return {};
}

template <typename C>
struct B
{
    typedef C In;
    typedef C Out;
};
template <typename C>
B<C> make_b()
{
    return {};
}

template <typename X, typename Y>
struct Join
{
    const X x;
    const Y y;
    
    typedef typename X::In In;
    typedef typename Y::Out Out;
};
template <typename X, typename Y>
Join<X,Y> make_join(X x, Y y)
{
    return {x, y};
}

int main() {
    make_join(make_a<int>(), make_b<int>());

	return 0;
}