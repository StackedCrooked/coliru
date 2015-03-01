int foo() { return 0; }
int foo(int) { return 1; }

template<typename F>
auto bar(F f) -> decltype( f(1) ) { return f(1); }

int main()
{
    // fine
    bar(foo);
    
    // wrong number of arguments to bar
    bar(foo, 0);
}