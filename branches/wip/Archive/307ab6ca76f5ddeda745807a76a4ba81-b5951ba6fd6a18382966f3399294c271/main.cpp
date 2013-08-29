namespace
{    
    constexpr unsigned fac(unsigned n)
    {
        return n == 0 ? 1
             : n * fac(n-1);
    }
    
    template<unsigned N>
    struct test { enum { value = N }; };
}

int main()
{
    #ifdef A
    return fac(0);
    #else
    return test<fac(0)>::value;
    #endif
}
