
#include <type_traits>

void f(struct nope);

template<class... Ts>
static void match(void(*)(Ts...));

template<class T>
struct exists_impl {
    template<class U>
    static auto test(int) -> decltype(match<U>(&f), std::true_type{});

    template<class U>
    static auto test(...) -> std::false_type;

    using type = decltype(test<T>(0));
};

template<class T>
struct exists : public exists_impl<T>::type {};

// Move this above struct trait to compile
void f(int);

int main() {
    static_assert(exists<int>::value, "le fail");
}
