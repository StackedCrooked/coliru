/*
 * integral_constant, true_type, false_type
 **/
  template<typename T, T valueT>
  struct integral_constant
  {
    static constexpr T value = valueT;
    using type = integral_constant<T,value>;
    constexpr operator T() { return value; }
  };
  // true_type/false_type
  using true_type = integral_constant<bool, true>;
  using false_type = integral_constant<bool, false>;

/*
 * reference-pointer transformations
 **/
  // add_lvalue_reference
  template<typename T> struct add_lvalue_reference { using type = T&; };
  template<> struct add_lvalue_reference<void> { using type = void; };
  template<> struct add_lvalue_reference<const void> { using type = const void; };
  template<> struct add_lvalue_reference<volatile void> { using type = volatile void; };
  template<> struct add_lvalue_reference<const volatile void>  { using type = const volatile void; };
  // add_rvalue_reference
  template<typename T> struct add_rvalue_reference { using type = T&&; };
  template<> struct add_rvalue_reference<void> { using type = void; };
  template<> struct add_rvalue_reference<const void> { using type = const void; };
  template<> struct add_rvalue_reference<volatile void> { using type = volatile void; };
  template<> struct add_rvalue_reference<const volatile void> { using type = const volatile void; };

  // remove_reference
  template <typename T> struct remove_reference      { using type = T; };
  template <typename T> struct remove_reference<T&>  { using type = T; };
  template <typename T> struct remove_reference<T&&> { using type = T; };

  // remove_pointer
  template<typename T> struct remove_pointer { using type = T; };
  template<typename T> struct remove_pointer<T*> { using type = T; };
  // is_const
  template<typename> struct is_const : false_type {};
  template<typename T> struct is_const<T const> : true_type {};
  // conditional
  namespace implementation
  {
    template<bool, typename First, typename Second> struct conditional { using type = First; };
    template<typename First, typename Second> struct conditional<false, First, Second> { using type = Second; };
  }
  template<bool B, typename First, typename Second> using conditional = typename implementation::conditional<B, First, Second>::type;
  // declval
  template<typename T> typename add_rvalue_reference<T>::type declval() noexcept;
  // add_const
  template<typename T> struct add_const { using type = const T; };
    // is_same
  template<typename, typename> struct is_same : false_type {};
  template<typename T> struct is_same<T,T> : true_type {};
template<typename> struct result_of;
template<typename T, typename Class, typename Thing>
struct result_of<T Class::*(Thing)> { using type = conditional<is_const<typename remove_pointer<Thing>::type>::value,
                                                               typename add_lvalue_reference<typename add_const<T>::type>::type,
                                                               typename add_rvalue_reference<T>::type>; };
template<typename T, typename Class, typename... ArgTypes>
struct result_of<T (Class::*)(ArgTypes...)> { using type = T; };
template<typename Function, typename... ArgTypes> struct result_of<Function(ArgTypes...)> { using type = decltype(declval<Function>()(declval<ArgTypes>()...)); };
  
// Standard's examples

typedef bool (&PF1)();
typedef short (*PF2)(long);
struct S {
operator PF2() const;
double operator()(char, int&);
void fn(long) const;
char data;
};
typedef void (S::*PMF)(long) const;
typedef char S::*PMD;
static_assert(is_same<result_of<S(int)>::type, short>::value, "Error!");
static_assert(is_same<result_of<S&(unsigned char, int&)>::type, double>::value, "Error!");
static_assert(is_same<result_of<PF1()>::type, bool>::value, "Error!");
//static_assert(is_same<result_of<PMF(unique_ptr<S>, int)>::type, void>::value, "Error!");
static_assert(is_same<result_of<PMD(S)>::type, char&&>::value, "Error!");
static_assert(is_same<result_of<PMD(const S*)>::type, const char&>::value, "Error!");

int main() {}
