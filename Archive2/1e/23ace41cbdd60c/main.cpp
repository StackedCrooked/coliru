#include <tuple>

template<typename S>
struct signature { };

template<typename R, typename... Args>
struct signature<R(Args...)>
{
    using return_type = R;
    using argument_type = std::tuple<Args...>;
};

// Test
#include <type_traits>

int main()
{
    using ret = signature<void(int, double)>::return_type;
    using arg1 = std::tuple_element_t<0, signature<void(int, double)>::argument_type>;
    using arg2 = std::tuple_element_t<1, signature<void(int, double)>::argument_type>;
    
    static_assert(std::is_same<ret, void>{}, "!");
    static_assert(std::is_same<arg1, int>{}, "!");
    static_assert(std::is_same<arg2, double>{}, "!");
}