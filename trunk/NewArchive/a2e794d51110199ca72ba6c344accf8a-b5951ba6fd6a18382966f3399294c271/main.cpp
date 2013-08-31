namespace
{    
    constexpr unsigned fib(unsigned n)
    {
        return n == 0 ? 0
             : n == 1 ? 1
             : (fib(n - 1) + fib(n - 2));
    }
    
    template<unsigned N>
    struct test { enum { value = N }; };
}

int main()
{
    #ifdef A
    return fib(0);
    #else
    return test<fib(0)>::value;
    #endif
}
