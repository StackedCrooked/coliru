#include <cstring>
#include <typeinfo>

class type_erased_mem_fun_ptr
{
    using comparison_function_t = bool(void const*, void const*);
    std::type_info const* tp;
    comparison_function_t* cmp;
    
    char buf[sizeof(void(type_erased_mem_fun_ptr::*)())];
    
    template<typename R, typename C, typename... Args>
    static bool compare(void const* const lhs, void const* const rhs)
    {
        using fun_t = R (C::*)(Args...);
        fun_t lhs_c;
        fun_t rhs_c;
        std::memcpy(&lhs_c, lhs, sizeof(lhs_c));
        std::memcpy(&rhs_c, rhs, sizeof(rhs_c));
        return lhs_c == rhs_c;
    }
    
public:
    template<typename R, typename C, typename... Args>
    type_erased_mem_fun_ptr(R (C::*p)(Args...))
        : tp( &typeid(p) )
        , cmp( &compare<R, C, Args...> )
    {
        static_assert(sizeof(buf) >= sizeof(p), "oops!");
        std::memcpy(buf, &p, sizeof(p));
    }
    
    friend bool operator==(type_erased_mem_fun_ptr const& lhs, type_erased_mem_fun_ptr const& rhs)
    {
        if(lhs.tp != rhs.tp) return false;
        return lhs.cmp(lhs.buf, rhs.buf);
    }
};

struct A
{
    bool foo(double, char) {}
    bool woot(int) {}
};

struct B
{
    virtual void meow() {}
};

#include <iostream>

int main()
{
    auto p0 = type_erased_mem_fun_ptr(&A::foo);
    auto p1 = type_erased_mem_fun_ptr(&A::woot);
    auto p2 = type_erased_mem_fun_ptr(&B::meow);
    
    std::cout << std::boolalpha;
    std::cout << (p0 == p0) << "\n";
    std::cout << (p0 == p1) << "\n";
    std::cout << (p0 == p2) << "\n";
}