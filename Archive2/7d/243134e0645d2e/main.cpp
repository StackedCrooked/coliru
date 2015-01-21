#include <functional>
#include <type_traits>
#include <boost/signals2/signal.hpp>

template<typename T>
struct signature_of;

template<typename R, typename... Args>
struct signature_of<std::function<R(Args...)>>
{
    using type = R(Args...);
};

template<typename T>
using signature_of_t = typename signature_of<T>::type;

template<typename T>
using signal_from_function = boost::signals2::signal<signature_of_t<T>>;

int main()
{
    using function_type = std::function<void(int)>;
    
    using signal_type = signal_from_function<function_type>;
    
    static_assert(std::is_same<signal_type, boost::signals2::signal<void(int)>>{}, "!");
}