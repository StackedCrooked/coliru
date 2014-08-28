#include <iostream>
#include <type_traits>
#include <typeinfo>

template< typename Policy >
struct policy_host_
: Policy
{
  using Policy::Policy;
};

template< typename Source, typename Target >
struct is_implicitly_convertible
: std::integral_constant<
    bool
  , std::is_constructible< policy_host_<Target>,  policy_host_<Source> >::value &&
    std::is_convertible<   policy_host_<Source>,policy_host_<Target>   >::value
  >
{  };

template< typename Source, typename Target >
struct is_explicitly_convertible
: std::integral_constant<
    bool
  , std::is_constructible< policy_host_<Target>,  policy_host_<Source> >::value &&
    !std::is_convertible<  policy_host_<Source>,policy_host_<Target>   >::value
  >
{  };

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

  template<
    class target_safety,
    typename std::enable_if<
      is_implicitly_convertible< target_safety, safety_policy >::value
    , bool>::type = false
  > Ptr( const Ptr<T, target_safety>& other )
  : safety_policy( other ),
    pointee_( other.pointee_ )
  { std::cout << "implicit Ptr constructor of " << typeid( *this ).name() << std::endl; }

  template<
    class target_safety,
    typename std::enable_if<
      is_explicitly_convertible< target_safety, safety_policy >::value
    , bool>::type = false
  > explicit Ptr( const Ptr<T, target_safety>& other )
  : safety_policy( other ),  //this is an explicit constructor call and will not preserve the implicity of conversion!
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
