  template<typename T, T value>
  struct integral_constant
  {
    //static constexpr T value = valueT;
    typedef integral_constant<T,value> type;
    constexpr operator T() { return value; }
  };
  // add_rvalue_reference
  template<typename T> struct add_rvalue_reference { typedef T&& type; };
  template<> struct add_rvalue_reference<void> { typedef void type; };
  template<> struct add_rvalue_reference<const void> { typedef const void type; };
  template<> struct add_rvalue_reference<volatile void> { typedef volatile void type; };
  template<> struct add_rvalue_reference<const volatile void> { typedef const volatile void type; };
  template<typename T> typename add_rvalue_reference<T>::type declval() noexcept;

  template<typename T, typename... Args> struct is_constructible : integral_constant<bool, sizeof(decltype(T(declval<Args>()...)))> {};
  
  
class A {};
class B { B() = delete; };

static_assert(is_constructible<A>(), "B");
static_assert(!is_constructible<B>(), "B");


int main(){}