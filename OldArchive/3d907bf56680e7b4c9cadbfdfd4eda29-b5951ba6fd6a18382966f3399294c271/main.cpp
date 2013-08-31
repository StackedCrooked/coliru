namespace
{    
    constexpr unsigned foo(unsigned n)
    {
        return n;
    }
    
    template<unsigned N>
    struct test { enum { value = N }; };
}

int main()
{
    #ifdef A
    return foo(0);
    #else
    return test<foo(0)>::value;
    #endif
}
