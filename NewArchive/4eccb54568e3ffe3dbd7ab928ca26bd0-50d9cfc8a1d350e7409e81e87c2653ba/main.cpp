  template<typename T, T value>
  struct integral_constant
  {
    //static constexpr T value = valueT;
    typedef integral_constant<T,value> type;
    constexpr operator T() { return value; }
  };
  
  // true_type
  typedef integral_constant<bool, true> true_type;
  // false_type
  typedef integral_constant<bool, false> false_type;
  // add_rvalue_reference
  template<typename T> struct add_rvalue_reference { typedef T&& type; };
  template<> struct add_rvalue_reference<void> { typedef void type; };
  template<> struct add_rvalue_reference<const void> { typedef const void type; };
  template<> struct add_rvalue_reference<volatile void> { typedef volatile void type; };
  template<> struct add_rvalue_reference<const volatile void> { typedef const volatile void type; };
  template<typename T> typename add_rvalue_reference<T>::type declval() noexcept;
  
    // is_same
  template<typename, typename> struct is_same : false_type {};
  template<typename T> struct is_same<T,T> : true_type {};

  template<typename T, typename... Args> struct is_constructible
  {
    template<typename F>
    static auto test(int) -> decltype(T(declval<Args>()...), true_type{});
    template<typename>
    static auto test(...) -> false_type;

    constexpr operator bool() { return decltype(test<T>(0))(); }
  };

class A { public: A(); A(int); };
class B { B() = delete; B(const B&) = delete;};
class C { C(); };

static_assert(is_constructible<A>(), "public: A()");
static_assert(is_constructible<A,int>(), "public: A(int)");
static_assert(!is_constructible<B>(), "B() = delete");
static_assert(!is_constructible<C>(), "private: C()");

int main(){}
