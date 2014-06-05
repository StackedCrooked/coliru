#include <iostream>
#include <functional>
#include <memory>
#include <type_traits>

namespace detail {
using FunPtr = void (*)(void*);

template <typename Lambda>
struct ClosureHelpers {
    using LambdaValue = typename std::remove_reference<Lambda>::type;
    template <typename... Args>
    using RetVal = typename std::result_of<Lambda(Args...)>::type;

    template <typename... Args>
    static RetVal<Args...> invoke(Args... args, void* data) {
        std::cerr << "invoked\n";
        return static_cast<LambdaValue*>(data)->operator()(args...);
    }

    static void destroy(void* data) {
        std::cerr << "destroyed\n";
        delete static_cast<LambdaValue*>(data);
    }
};
}

struct UnsafeClosure {
    detail::FunPtr invoke;
    detail::FunPtr destroy;
    void* data;
};

template <typename... Args>
class Closure {
    detail::FunPtr invoke;
    std::unique_ptr<void, detail::FunPtr> lambda;

public:
    template <typename T, typename Lambda = typename detail::ClosureHelpers<T>::LambdaValue>
    Closure(T&& lambda)
        : invoke(&detail::ClosureHelpers<T>::template invoke<Args...>),
          lambda(new Lambda(std::forward<T>(lambda)), &detail::ClosureHelpers<T>::destroy) {
        std::cerr << "created\n";
    }

    bool valid() const { return bool(lambda); }

    UnsafeClosure unsafe_get() {
        auto destroy = lambda.get_deleter();
        auto data = lambda.release();
        return {invoke, destroy, data};
    }
};

template <typename... Args, typename Lambda>
Closure<Args...> makeClosure(Lambda&& lambda) {
    return {lambda};
}

int main() {
    UnsafeClosure unsafe;

    {
        int num = 3;
        auto lambda = makeClosure<>([=] { std::cout << num << '\n'; });

        unsafe = lambda.unsafe_get();
    }

    unsafe.invoke(unsafe.data);
    unsafe.destroy(unsafe.data);
}
