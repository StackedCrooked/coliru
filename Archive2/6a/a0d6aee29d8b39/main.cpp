    #include <iostream>
    
    template< class T, unsigned S, unsigned SB >
    struct my_iterator;
    
    template< class T, unsigned S >
    struct my_iterator< T, S, 1 >
    { 
        static_assert ((S & (S - 1)) == 0, "S must be a power of 2");
        
        unsigned burp() {return (*p) + S;}
        
        T* p;
    };
    
    template< class T, unsigned S, unsigned SB = S >
    struct my_iterator : my_iterator< T, S, SB / 2 >
    {
    };
    
    int main()
    {
        int v = 10;
        
        my_iterator< int, 8 > a;
        a.p = &v;
        std::cout << a.burp() << std::endl;
        
        my_iterator< int, 8, 4 >& b = a;
        std::cout << b.burp() << std::endl;
        
        my_iterator< int, 1 > c;
        c.p = &v;
        std::cout << c.burp() << std::endl; // error: no member named 'burp'

        return 0;
    }