#include <memory>
#include <iostream>
#include <vector>
#include <deque>

/* SKIP THIS BOILERPLATE UNTIL LINE 86 */

namespace impl_ {

template<class T>
std::true_type is_foreachable_f(T&& value, decltype(std::begin(value))* = nullptr, decltype(std::end(value))* = nullptr){ return {}; }
std::false_type is_foreachable_f(...){ return {}; }
template<class T> using is_foreachable = decltype(is_foreachable_f(std::declval<T>()));

template<class R>
struct static_ifer_nil {
    R retval;
    
    static_ifer_nil(R&& val): retval(std::forward<decltype(retval)>(val)) {};
    
    template<class T>
    auto operator|(T&&) -> decltype(auto) {
        return *this;
    }
    
    template<class F>
    auto operator||(F&& f) -> decltype(auto) {
        return std::forward<decltype(retval)>(retval);
    }
    
    auto return_value() -> decltype(auto) {
        return std::forward<decltype(retval)>(retval);
    }
    
    template<class F>
    static static_ifer_nil make(F f) {
        return f(0, 0);
    }
};

template<>
struct static_ifer_nil<void> {
        
    template<class T>
    auto operator|(T&&) -> decltype(auto) {
        return *this;
    }
    
    template<class F>
    auto operator||(F&& f) -> decltype(auto) {
        return;
    }
    
    auto return_value() -> decltype(auto) {
        return;
    }
    
    template<class F>
    static static_ifer_nil make(F f) {
        f(0, 0);
        return {};
    }
};

struct static_ifer {    
    template<class F>
    auto checker(F f) -> static_ifer_nil<decltype(f(0,0))> {
        return static_ifer_nil<decltype(f(0,0))>::make(f);
    }
    auto checker(...) -> decltype(auto) {
        return *this;
    }
    
    template<class F>
    auto operator|(F f) -> decltype(auto) {
        return checker(f);
    }
    
    template<class F>
    auto operator||(F f) -> decltype(auto) {
        return checker(f).return_value();
    }

};

} /* namespace impl_ */

#define STATIC_IF(...) return impl_::static_ifer{} | [&](auto&& e, typename std::enable_if<(__VA_ARGS__), decltype(e)>::type checker) -> decltype(auto)
#define STATIC_ELSE_IF(...) | [&](auto&& e, typename std::enable_if<(__VA_ARGS__), decltype(e)>::type checker) -> decltype(auto)
#define STATIC_ELSE || [&](auto&&...) -> decltype(auto)

/* HERE COMETH THE FUN! */

template<class T>
auto first_element(T&& val) -> decltype(auto) {
    STATIC_IF(std::is_pointer<T>::value) {
        return *val;
    } STATIC_ELSE {
        return *std::begin(val);
    };
}

template<class T>
auto print(T&& val) -> decltype(auto) {
    STATIC_IF(impl_::is_foreachable<T>::value) {
        bool first = true;
        for(auto&& el : val) {
            if(!first) std::cout << ", ";
            std::cout << el;
            first = false;
        }
    } STATIC_ELSE_IF(std::is_pointer<T>::value) {
        std::cout << *val << std::endl;
    } STATIC_ELSE {
        std::cout << val << std::endl;
    };
}

int main() { 
    int x = 42;
    std::vector<int> v{1,2,3};
    std::cout << first_element(v) << std::endl; 
    first_element(&x) = 23;
    first_element(v) = 101;
    std::cout << first_element(v) << std::endl;
    std::cout << first_element(&x) << std::endl;
    
    print(2);
    print(&x);
    print(v);
}
