#include <type_traits>

struct default_check
{ 
  template<typename U>
  static std::false_type check(...);
};

struct is_addable : default_check
{
  using default_check::check;
    
  //template<typename U> static auto check(int) 
  //     -> decltype( std::declval<U>() + std::declval<U>(), std::true_type{});

  using type = decltype(check<void>(0));
};
int main()
{
}