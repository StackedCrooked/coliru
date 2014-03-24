
#include <type_traits>

template<class...>
void f(struct nope);

namespace impl {

template<class T, class... Ts>
struct hff {
    template<class U>
    static auto match(void(*)(Ts..., U&)) -> U;

    template<class U>
    using is_t = typename std::is_same<T, U>::type;

    template<class U> static auto test(int) -> is_t<decltype(match<U>(&f<Ts...>))>;
    template<class U> static auto test(int) -> is_t<decltype(match<U>(&f<Ts..., U>))>;
    template<class U> static auto test(...) -> std::false_type;

    typedef decltype(test<T>(0)) type;
};

}

template<class T, class... Ts>
struct has_non_member_f
    : public impl::hff<T, Ts...>::type
{};

// Move these above namespace impl and it works
struct S {};
template<class U> void f(U&, S&);

int main() {
    static_assert(has_non_member_f<S, int&>::value, "!!");
}
