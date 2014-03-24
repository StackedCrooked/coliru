
#include <type_traits>

void f(struct nope);

template<class T, class... Ts>
struct trait {
    template<class U>
    static auto match(void(*)(Ts..., U)) -> U;

    template<class U>
    using is_t = typename std::is_same<T, U>::type;

    template<class U> static auto test(int) -> is_t<decltype(match<U>(&f))>;
    template<class U> static auto test(...) -> std::false_type;

    static constexpr bool const
    value = decltype(test<T>(0))::value;
};

// Move this above struct trait to compile
void f(int, int&);

int main() {
    static_assert(trait<int&, int>::value, "le fail");
}
