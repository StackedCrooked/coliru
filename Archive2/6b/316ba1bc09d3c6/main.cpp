#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <exception>

struct Foo {
    Foo() { std::cout << "Foo Default CTOR" << std::endl; }
    Foo( Foo const & ) { std::cout << "Foo Copy CTOR" << std::endl; }
    Foo& operator=( Foo const & ) = delete;
    
    ~Foo() { std::cout << "Foo DTOR" << std::endl; }
};
template < typename T >
class MyVector
{
    public :
        MyVector() = default;
        MyVector( MyVector const & ) = delete;
        MyVector( MyVector && ) = default;
        
        MyVector& operator=( MyVector const & ) = delete;
        MyVector& operator=( MyVector && ) = default;
        
        T* data() { return reinterpret_cast<T*>( mem_.get() ); }
        T const* data() const{ return reinterpret_cast<T const*>( mem_.get() ); }
        
        T& at( size_t i ) {
            if ( i >= size_ ) throw std::out_of_range { "out of bounds" };
            return data()[i];
        }
        
        T const& at( size_t i ) const {
            if ( i >= size_ ) throw std::out_of_range { "out of bounds" };
            return data()[i];
        }
 
        size_t size() const
        {
            return size_;
        }
        size_t capacity() const
        {
            return capacity_;
        }
 
        void reserve( size_t capacity ) {
            if ( capacity_ >= capacity ) // only grow
                return;
            std::cout << "grow from " << capacity_ << " to " << capacity << std::endl;
            // allocate the new buffer and copy the current content
            std::unique_ptr<char[]> mem ( new char[ sizeof(T) * capacity ] );            
            T* tmp = reinterpret_cast<T*>( mem.get() );
            for( size_t i = 0; i != size_; ++ i )
                new ( tmp + i ) T( at(i) );
            
            // now that the content is copied, we are exception free ( destructor throw is undefined behavior ),
            // destroy old elements
            for( size_t i = 0; i != size_; ++ i )
                ( data() + i )->~T();
                
            mem_ = std::move( mem );
            capacity_ = capacity;
             std::cout << "grow suceeded" << std::endl;
        }
        
        void push_back( T const &p )
        {
            if ( size_ + 1 > capacity_ ) {
                reserve( capacity_ ? capacity_ * 2 : 1 );
            }
            new( data() + size_ ) T( p );
            size_++;
        }
 
        ~MyVector() {
            for( size_t i = 0; i != size_; ++ i )
                ( data() + i )->~T();
        }
    private :
        size_t size_     = 0;
        size_t capacity_ = 0;
        std::unique_ptr<char[]> mem_;
};

int main()
{
    Foo test;
    
    std::cout << "just before MyVector<Foo> creation" << std::endl;
    MyVector<Foo> tab;
    //tab.reserve( 2 );
    tab.push_back( test );
    tab.push_back( test );
    tab.push_back( test );
    tab.push_back( test );
    tab.push_back( test );
    tab.push_back( test );
    tab.push_back( test );
    tab.push_back( test );
   std::cout << "just before MyVector<Foo> destruction" << std::endl;
}
