#include <boost/bind.hpp>
#include <boost/function.hpp>

class A
{
  public:
    void aMethod( int );
};

class B
{
  public:
    template < class T >
    B( void (T::*method_ptr)(int),
       T * obj_ptr )
    {
      bCallAMethod( boost::bind( method_ptr, obj_ptr, _1 ) );
    }

    void bCallAMethod( boost::function< void (int ) > );
};

void A::aMethod( int x )
{
  printf("My number: %d\n", x);
}

void B::bCallAMethod( boost::function<void ( int ) > method_ptr )
{
  method_ptr( 5 );
}

int main( void )
{
  A a;
  B b( &A::aMethod, &a );
  return 1;
}