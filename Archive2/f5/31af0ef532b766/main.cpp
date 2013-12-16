#include <type_traits>

struct A {
    template<typename T>
    struct b {
        using type = T;
        constexpr bool g() const {
            return std::is_const<T>::value;
        }
    };
        
    constexpr auto f() const -> decltype(b<decltype(*this)>{}) {
        return {};
    }
};

int main() {
    const A x = {};    
    static_assert(x.f().g(), "..");
}