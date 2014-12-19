template<class ...>
using void_t = void;

// GCC workaround: 
// template<class...> struct voider { using type = void; }; 
// template<class... Args> using void_t = typename voider<Args...>::type;

template<class T, class = void>
struct pointer_type_or_default { 
    using type = typename T::value_type*;
};

template<class T>
struct pointer_type_or_default<T, void_t<typename T::pointer_type>> { 
    using type = typename T::pointer_type;
};

struct U { using value_type = int; };
int main() {
    pointer_type_or_default<U>::type test;
}