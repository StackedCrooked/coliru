template<typename Derived, typename... Types>
struct foo_base {};

template<typename Derived, typename First, typename... Rest>
struct foo_base<Derived, First, Rest...>: foo_base<Derived, Rest...> {
    Derived& operator=(First) { return static_cast<Derived&>(*this); }
    using foo_base<Derived, Rest...>::operator=;
};

template<typename... Types>
struct foo: foo_base<foo<Types...>, Types...> {
    using foo_base<foo<Types...>, Types...>::operator=;
};

int main()
{
    foo<int, double, int> f;
    f = 0.0;
}
