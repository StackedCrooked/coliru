    #include <iostream>
    
    template<class T>
    void print_type()
    {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }
    
    template <class T>
    int foo(bool) { return 42; }
    
    int bar(bool) { return 42; }
    
    template<class T>
    void deduce(T&&)
    {
        print_type<T>();
    }
    
    int main()
    {
        deduce(foo<bool>);
        deduce(bar);
    }