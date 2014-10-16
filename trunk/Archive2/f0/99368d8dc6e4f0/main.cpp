#include <cstddef>

namespace std14
{
    template<class T, T... Ints>
    class integer_sequence
    {
        using value_type = T;
    };

    namespace details
    {
        template<class T, std::size_t N> struct gen_int_seq;
        template<class T> struct gen_int_seq<T, 0> { using type = integer_sequence<T>; };
        template<class T> struct gen_int_seq<T, 1> { using type = integer_sequence<T, 0>; };
        template<class T> struct gen_int_seq<T, 2> { using type = integer_sequence<T, 0, 1>; };
        template<class T> struct gen_int_seq<T, 3> { using type = integer_sequence<T, 0, 1, 2>; };
        template<class T> struct gen_int_seq<T, 4> { using type = integer_sequence<T, 0, 1, 2, 3>; };
    }

    template<std::size_t... Ints>
    using index_sequence = integer_sequence<std::size_t, Ints...>;

    template<class T, T N>
    using make_integer_sequence = typename details::gen_int_seq<T, N>::type;

    template<std::size_t N>
    using make_index_sequence = make_integer_sequence<std::size_t, N>;

    template<class... T>
    using index_sequence_for = make_index_sequence<sizeof...(T)>;    
}

////////////////////////////////////////////////////////////////////////////////

#include <vector>

struct Foo {
    void func(bool, int) {}
};

Foo foo;

bool b;
int n;
std::vector<void*> v = {&b, &n};

template<typename T> T get(int i);
template<> bool get<bool>(int i) { return *static_cast<bool*>(v[i]); }
template<> int get<int>(int i) { return *static_cast<int*>(v[i]); }

struct Invoke
{
    template<typename... Ts, std::size_t... Is>
    void operator()(void(Foo::*f)(Ts...), std14::index_sequence<Is...>)
    {
        (foo.*f)(get<Ts>(Is)...);
    }
};

template<typename F>
struct DispatchHelper
{
    F* f;

    template<typename... Ts>
    void operator()(void(Foo::*m)(Ts...))
    {
        std14::index_sequence_for<Ts...> idx;
        (*f)(m, idx);
    }
};

int main()
{
    Invoke inv;
    DispatchHelper<Invoke> helper{&inv};
    helper(&Foo::func);
}
