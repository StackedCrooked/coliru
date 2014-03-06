    #include <typeinfo>
    #include <iostream>
    
    int main()
    {
        std::cout << typeid( '7' ).name() << std::endl ;
        std::cout << typeid( 7.0 ).name() << std::endl ;
        std::cout << typeid( "7" ).name() << std::endl ;
    }   