#include <iostream>
#include <memory>

struct NonCopyable
{
protected:
   NonCopyable() {}
private:
   NonCopyable( const NonCopyable& );
   NonCopyable& operator = ( const NonCopyable& );
};

struct A: private NonCopyable
{
   template< typename T >
   static std::unique_ptr< A > Create()
   {
      std::cout << __FUNCTION__ << std::endl;
      T t = T();
      return std::unique_ptr< A >( new A() );
   }
};

struct B: private NonCopyable
{
   B( std::unique_ptr< A >&& )
   {
      std::cout << __FUNCTION__ << std::endl;
   }
};

struct C: private NonCopyable
{
   C( B&& )
   {
      std::cout << __FUNCTION__<< std::endl;
   }
};

int main( int argc, char* argv[] )
{
   C c( B( A::Create< char >() ) );
   return 0;
}
