#include <tuple>
#include <iostream>

namespace detail
{
    template<bool c, bool v, bool lref, bool rref, class C, class Ret, class... Args>
    struct decompose_mem_fun_ptr_members
    {
        constexpr static bool is_const() { return c; }
        constexpr static bool is_volatile() { return v; }
        constexpr static bool is_lref() { return lref; }
        constexpr static bool is_rref() { return rref; }
        using return_type = Ret;
        using class_type = C;
        using arguments = std::tuple<Args...>;
        
        static void print()
        {
            std::cout << __PRETTY_FUNCTION__ << "\n";
        }
    };
}

template<class T>
struct decompose_mem_fun_ptr;

// no ref
template<class C, class Ret, class... Args>
struct decompose_mem_fun_ptr<Ret (C::*)(Args...)>
: detail::decompose_mem_fun_ptr_members<false, false, false, false, C, Ret, Args...>
{};

template<class C, class Ret, class... Args>
struct decompose_mem_fun_ptr<Ret (C::*)(Args...) const>
: detail::decompose_mem_fun_ptr_members<true, false, false, false, C, Ret, Args...>
{};

template<class C, class Ret, class... Args>
struct decompose_mem_fun_ptr<Ret (C::*)(Args...) volatile>
: detail::decompose_mem_fun_ptr_members<false, true, false, false, C, Ret, Args...>
{};

template<class C, class Ret, class... Args>
struct decompose_mem_fun_ptr<Ret (C::*)(Args...) const volatile>
: detail::decompose_mem_fun_ptr_members<true, true, false, false, C, Ret, Args...>
{};

// lref
template<class C, class Ret, class... Args>
struct decompose_mem_fun_ptr<Ret (C::*)(Args...) &>
: detail::decompose_mem_fun_ptr_members<false, false, true, false, C, Ret, Args...>
{};

template<class C, class Ret, class... Args>
struct decompose_mem_fun_ptr<Ret (C::*)(Args...) const &>
: detail::decompose_mem_fun_ptr_members<true, false, true, false, C, Ret, Args...>
{};

template<class C, class Ret, class... Args>
struct decompose_mem_fun_ptr<Ret (C::*)(Args...) volatile &>
: detail::decompose_mem_fun_ptr_members<false, true, true, false, C, Ret, Args...>
{};

template<class C, class Ret, class... Args>
struct decompose_mem_fun_ptr<Ret (C::*)(Args...) const volatile &>
: detail::decompose_mem_fun_ptr_members<true, true, true, false, C, Ret, Args...>
{};

//rref
template<class C, class Ret, class... Args>
struct decompose_mem_fun_ptr<Ret (C::*)(Args...) &&>
: detail::decompose_mem_fun_ptr_members<false, false, false, true, C, Ret, Args...>
{};

template<class C, class Ret, class... Args>
struct decompose_mem_fun_ptr<Ret (C::*)(Args...) const &&>
: detail::decompose_mem_fun_ptr_members<true, false, false, true, C, Ret, Args...>
{};

template<class C, class Ret, class... Args>
struct decompose_mem_fun_ptr<Ret (C::*)(Args...) volatile &&>
: detail::decompose_mem_fun_ptr_members<false, true, false, true, C, Ret, Args...>
{};

template<class C, class Ret, class... Args>
struct decompose_mem_fun_ptr<Ret (C::*)(Args...) const volatile &&>
: detail::decompose_mem_fun_ptr_members<true, true, false, true, C, Ret, Args...>
{};

struct foo
{
    bool bar(int, double, char) const &&;
};

int main()
{
    decompose_mem_fun_ptr<decltype(&foo::bar)>::print();
}
