// Functions that will be passed as arguments
int foo() { return 0; }
int foo(int i) { return 0; }

// Function template overloads
template<typename F>
int call(F f) {
    return f();
}

template<typename F, typename A>
int call(F f, A a) {
    return f(a);
}

int (*func_takes_void)() = foo;
int a = call(func_takes_void);

int (*func_takes_int)(int) = foo;
int b = call(func_takes_int, 0);