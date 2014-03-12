#include <iostream>
#include <type_traits>
#include <memory>

template<typename T>
struct has_shared_from_this {
    
    struct fallback {
        void shared_from_this();
    };
    
    struct derived : T, fallback {};
    
    template<typename U>
    static std::false_type test( std::integral_constant<void (fallback::*)(), &U::shared_from_this>* );
    
    template<typename>
    static std::true_type test(...);
    
    static constexpr bool value = decltype( test<derived>(nullptr) ){};
};

class A
{};

class C : private std::enable_shared_from_this<C>
{};

int main() {
    std::cout << std::boolalpha;
    std::cout << has_shared_from_this<A>::value << "\n";
    std::cout << has_shared_from_this<C>::value << "\n";
}
