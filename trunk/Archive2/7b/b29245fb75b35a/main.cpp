#include <iostream>
#include <tuple>
#include <type_traits>

// Plain-vanilla implementation of void_t
template<class...> struct voider { using type = void; };
template<class...Ts>
using void_t = typename voider<Ts...>::type;

// WrapperTraits #######################################

// Wrapper types specialize WrappedType to expose the type they wrap;
// a type T is a wrapper type iff the type WrappedType<T>::type exists.
template<class> struct WrappedType {};

// GetRootType unwraps any and all layers of wrappers.
template<class T, class = void>
struct GetRootType {
  using type = T; // The root type of a non-WrappedType is that type itself.
};

// The root type of a WrappedType is the root type of the type that it wraps.
template<class T>
struct GetRootType<T, void_t<typename WrappedType<T>::type>> :
  GetRootType<typename WrappedType<T>::type> {};

// non-WrappedTypes have no wrapper traits.
template<class T, class = void>
struct WrapperTraits {};

// WrappedTypes have two associated types:
// * WrappedType, the type that is wrapped
// * RootType, the fully-unwrapped type inside a stack of wrappers.
template<class T>
struct WrapperTraits<T, void_t<typename WrappedType<T>::type>> {
  using WrappedType = typename ::WrappedType<T>::type;
  using RootType = typename GetRootType<T>::type;
};

// Convenience aliases for accessing WrapperTraits
template<class T>
using WrapperWrappedType = typename WrapperTraits<T>::WrappedType;
template<class T>
using WrapperRootType = typename WrapperTraits<T>::RootType;

// Some wrappers #######################################

// Wrapper<T> is a WrappedType
template<class> struct Wrapper {};
template<class T>
struct WrappedType<Wrapper<T>> {
  using type = T;
};

// A single-element array is a WrappedType
template<class T>
struct WrappedType<T[1]> {
  using type = T;
};

// A single-element tuple is a WrappedType
template<class T>
struct WrappedType<std::tuple<T>> {
  using type = T;
};

// Test function #######################################

void f(int) {
  std::cout<<"int"<<std::endl;
}

template<class T>
auto f(T) ->
  typename std::enable_if<
    std::is_same<int,WrapperRootType<T>>::value
  >::type
{
  std::cout<<"Wrapper<...<int>...>"<<std::endl;
  f(WrapperRootType<T>{});
}


int main() {
  f(Wrapper<int>{});  
  f(Wrapper<std::tuple<Wrapper<Wrapper<Wrapper<int[1]>[1][1][1]>[1]>[1]>[1]>{});
}
