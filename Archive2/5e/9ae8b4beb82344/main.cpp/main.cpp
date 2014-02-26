    #include <iostream>
    #include <typeinfo>
    
    int main()
    {
        std::cout << typeid( [] () { return true ; } ).name() << std::endl ;
        std::cout << typeid( [] () { return true ; } ).name() << std::endl ;
        std::cout << typeid( [] () { return true ; } ).name() << std::endl ;
    }