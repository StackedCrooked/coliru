#include <type_traits>

template<class T>
struct is_complete{
    template<class U>
    static auto test(int) -> decltype(sizeof(U), std::true_type{});
    template<class>
    static auto test(...) -> std::false_type;
    
    static constexpr bool value = decltype(test<T>(0))::value;
};

struct X;
struct Y{};

static_assert(is_complete<X>::value, "X");
static_assert(is_complete<Y>::value, "Y");

int main(){
}