#include <iostream>
#include <string>
#include <vector>

template<typename T> struct HasValueType { 
    struct Fallback { T value_type; }; 
    struct Derived : T, Fallback { };

    template<typename C, C> struct ChT; 

    template<typename C> static char (&f(ChT<int Fallback::*, &C::value_type>*))[1]; 
    template<typename C> static char (&f(...))[2]; 

    static bool const value = sizeof(f<Derived>(0)) == 2;
}; 

template <typename T>
typename std::enable_if<HasValueType<T>::value, typename T::value_type>::type
proxy_func_op() {

}
    
template <typename T>
typename std::enable_if<!HasValueType<T>::value, T>::type
proxy_func_op() {
     
}

template <typename T>
typename std::enable_if<HasValueType<T>::value, typename T::const_iterator>::type
proxy_func_mem() {
}

template <typename T>
typename std::enable_if<!HasValueType<T>::value, T*>::type
proxy_func_mem() {
}


template<typename T>
class MyIterator {
    decltype(proxy_func_mem<T>()) begin;
    decltype(proxy_func_mem<T>()) end;
    decltype(proxy_func_mem<T>()) cur;
public:
    template <typename U = T>
    typename std::enable_if<HasValueType<U>::value, void>::type 
    init(U t) {
        static_assert(std::is_same<typename T::const_iterator, 
            decltype(proxy_func_mem<U>())>::value, 
            "Make sure correct function is called.");
        begin = t.begin();
        end = t.end();
        cur = begin;
    }
    
    template <typename U = T>
    typename std::enable_if<!HasValueType<U>::value, void>::type 
    init(U t) {
        static_assert(!std::is_same<typename T::const_iterator, 
        decltype(proxy_func_mem<U>())>::value, 
        "Make sure correct function is called.");
        cur = &t;
    }

    explicit MyIterator(const T& t) {
        init<T>(t);
    }
    
    MyIterator& operator++() {
        static_assert(HasValueType<T>::value, "You cannot use this operator for non-containers.");
        if (cur + 1 != end)
            cur++;
        return *this;
    }
    
    decltype(proxy_func_op<T>()) operator *() {
        return *cur;
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> vi = { 1, 2, 3, 4, 5 };
    MyIterator<std::vector<int>> vec_it(vi);
    for (unsigned int i = 0; i < vi.size(); i++) {
        std::cout << *vec_it << std::endl;
        ++vec_it;
    }
    
    std::string s = "hi";
    MyIterator<std::string> s_it(s);
    for (unsigned int i = 0; i < s.size(); i++) {
        std::cout << *s_it<< std::endl;
        ++s_it;
    }
    
    return 0;
}
