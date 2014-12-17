#include <cstddef>

// Get ref to any type, used in expression SFINAE
template<typename T>
T& declval();

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
int foo() { return 0; }
// int foo(int i) { return 0; }


// Function template overloads
// Use SFINAE to choose function pointer type F with appropriate signature.
template<typename F>
typename expr_check<sizeof(declval<F>()()), typename func_ptr_result<F>::type>::type
call(const F& f) {
    return f();
}

template<typename F, typename A>
typename expr_check<sizeof(declval<F>()(declval<A>())), typename func_ptr_result<F>::type>::type
call(F f, A a) {
    return f(a);
}


// Positive control: explicitly specify the type of the pointer to foo.
int (*func_takes_void)() = foo;
int a = call(func_takes_void);

// int (*func_takes_int)(int) = foo;
// int b = call(func_takes_int, 0);


// Only provide function name.  Try to deduce type of pointer.
// Won't compile.  clang and gcc: "no matching function"
// Either one alone is enough for the error.
int c = call(&foo);
// int d = call(&foo, 0);
// If foo(void) definition is commmented out then the line above compiles.

// Is there any way to get `call(foo)` and `call(foo, 5)` to compile without
// explicitly providing the types?