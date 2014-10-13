#include <iostream>
#include <type_traits>

namespace detail
{
    template <typename U, void(U::*)()>
    using SFINAE = void;
    
    template <typename U>
    static std::true_type has_non_const_operator(SFINAE<U, &U::operator()>*);
    
    template <typename U>
    static std::false_type has_non_const_operator(...);
}

// T&, operator const -> no copy
// const T&, operator const -> no copy
// T&&, operator non-const -> no copy
// T&&, operator const -> no copy
// const T&&, operator const -> no copy

// T&, operator non-const -> copy
// const T&, operator non-const -> copy
// const T&&, operator non-const -> copy

template <typename F>
using has_non_const_operator = decltype(detail::has_non_const_operator<std::decay_t<F>>(nullptr));

template <typename F>
using safe_mutual_handler_type = std::conditional_t<
                 (std::is_lvalue_reference<F>::value || std::is_const<F>::value)
                 && has_non_const_operator<std::decay_t<F>>::value,
                 std::decay_t<F>,
                 F&&>;

template <typename F>
void wrapper(F&& func)
{
    safe_mutual_handler_type<F> tmp = std::forward<F>(func);
    tmp();
}

struct Functor
{
    Functor() {}
    Functor(const Functor&) { std::cout << "Functor(const Functor&)" << std::endl; }
    void operator()() const { std::cout << "operator() const" << std::endl; }
};

const Functor make_functor()
{
    return Functor{};
}

struct NonConstFunctor
{
    NonConstFunctor() {}
    NonConstFunctor(const NonConstFunctor&) { std::cout << "NonConstFunctor(const NonConstFunctor&)" << std::endl; }
    void operator()() { std::cout << "operator()" << std::endl; }
};

const NonConstFunctor make_non_const_functor()
{
    return NonConstFunctor{};
}

int main()
{    
    // const-operator()
    
    // 1. rvalue reference:
    wrapper(Functor());
    
    // 2. lvalue reference:
    Functor f; wrapper(f);
    
    // 3. const lvalue reference:
    const Functor cf; wrapper(cf);
    
    // 4. const rvalue reference:
     wrapper(make_functor());
     
    // non-const operator()
    
    // 1. rvalue reference:
    wrapper(NonConstFunctor());
    
    // 2. lvalue reference:
    NonConstFunctor ncf; wrapper(ncf);
    
    // 3. const lvalue reference:
    const NonConstFunctor cncf; wrapper(cncf);
    
    // 4. const rvalue reference:
    wrapper(make_non_const_functor());
}
