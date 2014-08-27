#include <iostream>
#include <type_traits>
#include <typeinfo>

struct NoChecking;
struct NotNull;

struct NoChecking{
  NoChecking()                    = default;
  NoChecking( const NoChecking&)  = default;

  explicit NoChecking( const NotNull& )
  { std::cout << "explicit conversion constructor of NoChecking" << std::endl; }

protected:
  ~NoChecking() {} //defaulting the destructor in GCC 4.8.1 makes it public somehow :o
};

struct NotNull{
  NotNull()                 = default;
  NotNull( const NotNull&)  = default;

  NotNull( const NoChecking& )
  { std::cout << "explicit conversion constructor of NotNull" << std::endl; }

protected:
  ~NotNull()    {}
};

template<
  typename T,
  class safety_policy
> class Ptr
: public safety_policy
{
private:
  T* pointee_;

public:
  template <
    typename f_T,
    class f_safety_policy
  > friend class Ptr;   //we need to access the pointee_ of other policies when converting
                        //so we befriend all specializations of Ptr
public:

    //implicit conversion operator
  template<
    class target_safety
  > operator Ptr<T, target_safety>() const {
    std::cout << "implicit conversion operator of " << typeid( *this ).name() << std::endl;

    struct target_host : target_safety { using target_safety::target_safety; };

    static_assert( std::is_convertible<Ptr, target_host>::value,
                     //Now this works, because target_host is constructible!
                  "Safety policy of *this is not implicitly convertible to target's safety policy." );

      //calls the explicit conversion constructor of the target type
    return Ptr< T, target_safety >( *this );
  }

    //explicit conversion constructor
  template<
    class target_safety
  > explicit Ptr( const Ptr<T, target_safety>& other )
  : safety_policy( other ),  //this is an explicit constructor call and will call explicit constructors when we make Ptr() constructor implicit!
    pointee_( other.pointee_ )
  { std::cout << "explicit Ptr constructor of " << typeid( *this ).name() << std::endl; }

  Ptr() = default;
};

  //also binds to temporaries from conversion operators
void test_noChecking( const Ptr< int, NoChecking >& )
{  }

void test_notNull( const Ptr< int, NotNull >& )
{  }

int main()
{
  Ptr< int, NotNull    > notNullPtr;                //enforcing not null value not implemented for clarity
  Ptr< int, NoChecking > fastPtr( notNullPtr );     //OK - calling explicit constructor and NotNull is explicitly convertible to NoChecking

  test_notNull    ( fastPtr    );    //should be OK    - NoChecking is implictly convertible to NotNull
  test_noChecking ( notNullPtr );    //should be ERROR - NotNull is explicitly convertible to NoChecking

  return 0;
}
