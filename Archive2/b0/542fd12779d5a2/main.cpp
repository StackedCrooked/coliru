#include <boost/any.hpp>
#include <functional>

template<typename Signature> struct Function;
template<typename Ret, typename... Args> class Function<Ret(Args...)>  {
    boost::any storage;
    struct callable {
        virtual Ret call(Args... args) = 0;
    };
    template<typename F> struct derived : public callable {
        derived(F f)
            : obj(std::move(f)) {}
        F obj;
        Ret call(Args... args) { return obj(std::forward<Args>(args)...); }
    };
public:
    template<typename F> Function(F f, typename std::enable_if<!std::is_same<Function, F>::value>::type* = 0) {
        storage = derived<F>(std::move(f));
    }
    
    Function(const Function&) = default;
    Function(Function&&) = default;
    Function& operator=(const Function&) = default;
    Function& operator=(Function&&) = default;
    
    Ret operator()(Args... args) {
        if (auto call = boost::any_cast<callable>(&storage))
            return call->call(std::forward<Args>(args)...);
        throw std::bad_function_call();
    }
};