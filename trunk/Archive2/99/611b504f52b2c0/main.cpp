#include <functional>

namespace detail {
    extern "C" {
        template<typename Ret, typename... Args>
        using extern_c_fp = Ret(*)(Args...);
    }
}

template<typename Signature>
class bound_function;

template<typename Ret, typename... Args>
class bound_function<Ret(Args...)> {
public:
    template<typename F>
    explicit bound_function(F function_) : function(std::move_function_) { }

    operator detail::extern_c_fp<Ret, Args...>() const;

private:
    std::function<Ret(Args...)> function;
};

int main() {
    return 0;
}
