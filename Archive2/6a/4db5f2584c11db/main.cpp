#include <type_traits>
#include <iostream>
#include <string>

struct default_check
{
  template<class>
  static std::false_type check(...);
};

template<typename T>
struct is_addable : default_check
{
  using default_check::check;
    
  template<typename U> static auto check(int) 
       -> decltype( std::declval<U>() + std::declval<U>(), std::true_type{});

  using type = decltype(check<T>(0));
};

template<typename T>
struct is_multiplicable : default_check
{
  using default_check::check;
  
  template<typename U> static auto check(int)
    -> decltype( std::declval<U>() * std::declval<U>(), std::true_type{});
    
  using type = decltype(check<T>(0));
};

int main()
{
  std::cout <<"is_addable\n";
  std::cout <<" long:   "<< std::boolalpha << is_addable<long>::type::value        <<'\n';
  std::cout <<" string: "<< std::boolalpha << is_addable<std::string>::type::value <<'\n';
  std::cout <<" void:   "<< std::boolalpha << is_addable<void>::type::value        <<'\n';
  
  std::cout <<"is_multiplicable\n";
  std::cout <<" long:   "<< std::boolalpha << is_multiplicable<long>::type::value        <<'\n';
  std::cout <<" string: "<< std::boolalpha << is_multiplicable<std::string>::type::value <<'\n';
  std::cout <<" void:   "<< std::boolalpha << is_multiplicable<void>::type::value        <<'\n';
}