#include <utility>
#include <functional>
#include <memory>

#include <boost/optional.hpp>

template<typename F, typename Pointer>
struct wrap_type {
    F f;
    Pointer pointer;

    template<typename... Rest>
    auto operator()(Rest&&... rest)
    -> boost::optional<decltype( f(*pointer.lock(), std::forward<Rest>(rest)...) )>
    {
        if(auto p = pointer.lock()) {
            return f(*p, std::forward<Rest>(rest)...);
        } else {
            return {};
        }
    }
};

template<typename F, typename Pointer>
wrap_type<typename std::decay<F>::type, typename std::decay<Pointer>::type>
wrap(F&& f, Pointer&& pointer)
{ return { std::forward<F>(f), std::forward<Pointer>(pointer) }; }

#include <iostream>

int main()
{
    auto p = std::make_shared<int>(42);
    auto w = std::weak_ptr<int> { p };
    
    auto add = [](int i, int j) { return i + j; };
    auto f = wrap(add, std::move(w));
    
    {
        auto result = f(3);
        std::cout << std::boolalpha;
        std::cout << "result empty:\t" << !result << '\n';
        if(result) std::cout << "result:\t" << *result << '\n';
    }
    
    p.reset();
    {
        auto result2 = f(6);
        std::cout << std::boolalpha;
        std::cout << "result2 empty:\t" << !result2 << '\n';
        if(result2) std::cout << "result2:\t" << *result2 << '\n';
    }
}