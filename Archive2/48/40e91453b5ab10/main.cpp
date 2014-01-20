#include <type_traits>

template<class T> struct Base{
  typedef T type;
  T t;
};

template<class T> struct A : Base<T>{
  static constexpr T value = 1;
};
template<class T> struct B : Base<T>{
  static constexpr T value = 2;
};

struct Unrelated{};

// etc.

template<typename,typename = void> struct IsBase : std::false_type {};
template<typename T> struct IsBase<T, typename std::enable_if<std::is_base_of<Base<typename T::type>,T>::value>::type> : std::true_type {};

template<class T> typename std::enable_if<IsBase<T>::value>::type foo(T t){
    // use T::value
    static_assert( T::value >= 0, "" );
}

template<class T> typename std::enable_if<!IsBase<T>::value>::type foo(T t){
    // general case
}

int main(){
  foo(A<float>());//do something special based on value fields of A and B
  foo(B<float>());
  foo(Unrelated()); //do some default behavior
}
