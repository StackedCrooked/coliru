#include <iostream>

template< typename T > struct my_ptr : my_ptr< const T >
{
    using my_ptr<const T>::my_ptr;
    T& operator*() const { return *this->p_; }
};

template< typename T > struct my_ptr< const T >
{
protected:
    T* p_;
    
public:
    explicit my_ptr( T* p )
      : p_(p)
    {
        std::cout << "my_ptr<const T>::my_ptr(T*)" << std::endl;
    }
    
    // just to test nothing is copied
    my_ptr( const my_ptr& p ) = delete;

    ~my_ptr()
    {
        delete p_;
        std::cout << "my_ptr<const T>::~my_ptr()" << std::endl;
    }

    const T& operator*() const { return *p_; }
};

void f( const my_ptr< const int >& p )
{
    // *p = 1; // error

    std::cout << "inside f(...)" << std::endl;
    std::cout << *p << std::endl;
}

int main()
{
    my_ptr<int> p( new int( 0 ) );
    *p = 42; std::cout << *p << std::endl;
    std::cout << "before f(...)" << std::endl;
    f( p );
    std::cout << "after f(...)" << std::endl;
    *p = 5; std::cout << *p << std::endl;
}
