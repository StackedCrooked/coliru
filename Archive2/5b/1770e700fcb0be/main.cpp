#include <type_traits>
#include <ostream>
#include <utility>
#include <string>
#include <typeinfo>
#include <memory>
#include <iostream>

#include <cxxabi.h>

template <class ...Args>
struct Helper;

template <class F, class T>
struct Helper<F, T, std::tuple<>> {
    using type = std::tuple<T>;
};

template <class F, class T, class ...Args>
struct Helper<F, T, std::tuple<Args...>> {
    using t1 = typename F::template apply<T>;
    using type = std::tuple<t1, Args...>;
};

template <class F, class ...Args>
struct Map;

template <class F>
struct Map<F, std::tuple<>> {
    using type = std::tuple<>;
};

template <class F, class T, class ...Args>
struct Map<F, std::tuple<T, Args...>> {
    using type = typename Helper<F, T, typename Map<F, typename std::tuple<Args...>>::type>::type;
};


template <class T>
    std::string type_description() {
        bool is_lvalue_reference = std::is_lvalue_reference<T>::value;
        bool is_rvalue_reference = std::is_rvalue_reference<T>::value;
        bool is_const = std::is_const<typename std::remove_reference<T>::type>::value;
        
        std::unique_ptr<char, void(*)(void*)>
        name {abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr), std::free};
        
        auto str = std::string(name.get());
        if (is_const) {
            str += " const";
        }
        if (is_lvalue_reference) {
            str += "&";
        }
        if (is_rvalue_reference) {
            str += "&&";
        }
        
        return str;
    }
    
struct Func {
    template <class T>
    using apply = typename std::add_rvalue_reference<T>::type;
};

int main () { 
    std::cout << type_description<Map<Func, std::tuple<int, double , int const>>::type>();
}