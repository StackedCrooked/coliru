#include <utility>
#include <iostream>
#include <string>

template < typename T > struct megaptr
{
    template< typename... CONSTRUCTOR_ARGS > megaptr( CONSTRUCTOR_ARGS&&... args )
        : ptr( new T( std::forward<CONSTRUCTOR_ARGS>(args)... ) )
          { std::cout << "created object of type T at address " << ptr << '\n' ; }

     ~megaptr()
     {
         std::cout << "destroy object of type T at address " << ptr << '\n' ;
         // delete commented out to avoid double delete (undefined behavior)
         // delete ptr ;
     }

    T& operator*() { return *ptr ; }
    T* operator-> () { return &**this ; }

    // ...

    private: T* ptr ;
};

int main()
{
    megaptr<int> ptr_one(123) ;
    std::cout << "ptr_one created\n" ;

    {
        megaptr<int> ptr_two(5678) ; 
        std::cout << "ptr_two created\n" ;
        
        ptr_two = ptr_one ; // copy assignment
        // what happens to the object originally 'pointed to' by ptr_two?
        // what does ptr_two 'point to' after this assignment?
        
        std::cout << "about to destroy ptr_two\n" ; // life-time of ptr_two is almost over
    }   

    // what about the object that ptr_one 'pointer to'?

    std::cout << "about to destroy ptr_one\n" ; // life-time of ptr_one is almost over
}
