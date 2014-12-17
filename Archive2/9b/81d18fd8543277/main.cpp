#include <cstddef>

// Get ref to any type, used in expression SFINAE
template<typename T>
T& declval();
// std::declval<>() is fine too

#include <utility>

// Expression SFINAE tool, first parameter is an expression used for
// SFINAE, second parameter is passed through as a typedef
template<std::size_t, typename type_>
struct expr_check
{
    typedef type_ type;
};

// Return type deduction
template<class T>
struct func_ptr_result{};

template<class R>
struct func_ptr_result<R (*)()>
{
    typedef R type;
};

template<class R, class Arg1>
struct func_ptr_result<R (*)(Arg1)> {
    typedef R type;
};


// Functions that will be passed as arguments
// Commenting out foo() allows the portion at the bottom to compile.
int foo() { return 7; }
int foo(int i) { return i + 7; }


// Function template overloads
// Try to overload based on signature of function, F.

// This first overload is not necessary for the compile error but changes to
// the code must not break this.
template<typename F>
typename expr_check<sizeof(declval<F>()()), typename func_ptr_result<F>::type>::type
call(const F& f) {
    return f();
}

template<typename F, typename A>
typename expr_check<sizeof(declval<F>()(declval<A>())), typename func_ptr_result<F>::type>::type
call(const F& f, const A& a) {
    return f(a);
}


// Positive control: explicitly specify the type of the pointer to foo.
// These calls are not necessary for the compile error but changes to
// the code must not break this.
int (*func_takes_void)() = foo;
int i = call(func_takes_void);

int (*func_takes_int)(int) = foo;
int j = call(func_takes_int, 5);


// Only provide function name.  Try to deduce type of pointer.
// Won't compile.  clang and gcc: "no matching foo for call to 'call'"
int k = call(foo, 5);
// If foo() definition is commmented out above, this will compile.

// Is there any way to get `call(foo, 5)` to compile without
// explicitly providing the function pointer type?


// no main() because it's a bit cliche don't you think?