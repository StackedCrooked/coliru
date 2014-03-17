    #include <cstddef> // for std::size_t
    #include <type_traits> // for std::integral_constant
    
    template<size_t Index, int ...Values> 
    struct indexer;
    
    template<size_t Index> 
    struct indexer<Index>
    {
        // provide a dummy to allow simple overloading via a using-declaration
        // if you see a linker error here, the Value could not be found
        template<int Value>
        size_t get(std::integral_constant<int, Value>);
    };
    
    template<size_t Index, int T, int ...Rest>
    struct indexer<Index, T, Rest...> :
        public indexer<Index + 1, Rest...>
    {
        template<int Value>
        size_t get()
        {
            return get(std::integral_constant<int, Value>());
        }
        
        // a using-declaration to allow overloading
        using typename indexer<Index + 1, Rest...>::get;
        
        size_t get(std::integral_constant<int, T>)
        { return Index; }
    };
    
    // this class (should) maps Values... to 0,1,2...
    template<int ...Values>
    struct mapper :
        public indexer<0, Values...>
    {};
    
    #include <iostream>
    int main()
    {
        mapper<5, 2, 3> m;
        std::cout << m.get<5>();   // returns 0 as expected
        std::cout << m.get<2>();   // does not compile
    }