#include <type_traits>
#include <tuple>

template<typename... Args>
struct types { typedef types type; };

template<typename TFuncSignature>
struct function_traits;

template<typename T, typename R, typename... Args>
struct function_traits<R(T::*)(Args...)> {
    static const std::size_t arity = sizeof...(Args);
    static const bool is_member_function = true;
    typedef std::tuple<Args...> arg_tuple_type;
    typedef types<Args...> args_type;
    typedef R(T::* function_pointer_type)(Args...);
    typedef typename std::remove_pointer<function_pointer_type>::type function_type;
    typedef R(*free_function_pointer_type)(Args...);
    typedef R return_type;
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};

template<typename T, typename R, typename... Args>
struct function_traits<R(T::*)(Args...) const> {
    static const std::size_t arity = sizeof...(Args);
    static const bool is_member_function = true;
    typedef std::tuple<Args...> arg_tuple_type;
    typedef types<Args...> args_type;
    typedef R(T::* function_pointer_type)(Args...);
    typedef typename std::remove_pointer<function_pointer_type>::type function_type;
    typedef R(*free_function_pointer_type)(Args...);
    typedef R return_type;
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};

template<typename R, typename... Args>
struct function_traits<R(Args...)> {
    static const std::size_t arity = sizeof...(Args);
    static const bool is_member_function = false;
    typedef std::tuple<Args...> arg_tuple_type;
    typedef types<Args...> args_type;
    typedef R(function_type)(Args...);
    typedef R(*function_pointer_type)(Args...);
    typedef R(*free_function_pointer_type)(Args...);
    typedef R return_type;
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};

template<typename R, typename... Args>
struct function_traits<R(*)(Args...)> {
    static const std::size_t arity = sizeof...(Args);
    static const bool is_member_function = false;
    typedef std::tuple<Args...> arg_tuple_type;
    typedef types<Args...> args_type;
    typedef R(function_type)(Args...);
    typedef R(*function_pointer_type)(Args...);
    typedef R(*free_function_pointer_type)(Args...);
    typedef R return_type;
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};

template<class... Args, class R>
void set(R fun_ptr(Args...)){}

template<class Sig>
void set(Sig* fun_ptr){}

template<class... Args, class R, class C>
void set(R (C::*mem_ptr)(Args...)){}

template<class Sig, class C>
void set(Sig C::* mem_ptr){}

template<class T> struct type{};

template<class... Args, class F,
    class = typename std::result_of<F&(Args...)>::type> // SFINAE
void set_i(type<Args...>, F f){}

template<class R, class... Args, class F,
    class E = typename std::result_of<F&(Args...)>::type> // SFINAE
void set_i(type<R(Args...)>, F f){}

template<class Sig, class F>
auto set(F f)
    -> decltype(set_i(type<Sig>{}, f))
{}

void f(int){}
void f(int, int){}

struct X{
    void f(int){}
    void f(int, int){}
};

struct Y{
    void operator()(int){}
    void operator()(int, int){}
};

int main(){
    /*set<int>(f);
    set<int, int>(f);
    set<void(int, int)>(f);
    //set<int*>(f); // OR fail
    set<int>(&X::f);
    set<int, int>(&X::f);
    set<void(int, int)>(&X::f);
    //set<int*>(&X::f); // OR fail
    */
    set<int>(Y{});
    set<int, int>(Y{});
    set<void(int, int)>(Y{});
    //set<int*>(Y{}); // OR fail
}