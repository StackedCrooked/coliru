#include <type_traits>

template<typename S>
struct signature { };

template<typename R, typename Arg>
struct signature<R(Arg)>
{
    using return_type = R;
    using argument_type = Arg;
};

int main()
{
    using ret = signature<void(int)>::return_type;
    using arg = signature<void(int)>::argument_type;
    
    static_assert(std::is_same<ret, void>{}, "!");
    static_assert(std::is_same<arg, int>{}, "!");
}