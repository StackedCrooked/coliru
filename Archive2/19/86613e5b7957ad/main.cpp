#include <tuple>
#include <type_traits>
#include <utility>
#include <iostream>

// not decay, I don't want array->pointer or function->function pointer conversion:
template<class T>
using cleanup_t = std::remove_cv_t< std::remove_reference_t< T > >;



template<class T,size_t s0=std::tuple_size<cleanup_t<T>>{}>
struct tuple_slicer{
  T&&t;
  template<class Dest,size_t s1=std::tuple_size<Dest>{}>
  Dest get() && {
    using indexes=std::make_index_sequence<(s0<s1)?s0:s1>;
    return std::move(*this).template get<Dest>(indexes{});
  }
  template<class Dest,size_t s1=std::tuple_size<Dest>{},size_t...is>
  Dest get(std::index_sequence<is...>) && {
    static_assert(s0>=s1,"use slice_tuple on target");
    using std::get;
    return Dest{ get<is>(std::forward<T>(t))... };
  }
  template<class Dest>
  operator Dest()&&{
    return std::move(*this).template get<Dest>();
  }
  template<class Src, size_t...is>
  void assign(std::index_sequence<is...>,tuple_slicer<Src>&&rhs)&&{
    using std::get;
    int _[]={0,(void(
      get<is>(std::forward<T>(t))=get<is>(std::forward<Src>(rhs.t))
    ),0)...};
    (void)_; // remove warnings
  }
  template<class Src,size_t s1>
  void operator=(tuple_slicer<Src,s1>&&rhs)&&{
    using indexes=std::make_index_sequence<(s0<s1)?s0:s1>;
    std::move(*this).assign(indexes{},std::move(rhs));
  }
  template<class Src>
  void operator=(Src&& src)&&{
      std::move(*this) = tuple_slicer<Src>{ std::forward<Src>(src) };
  }
};

template<class Tuple>
tuple_slicer<Tuple> auto_slice(Tuple&&t){
  return {std::forward<Tuple>(t)};
}

int main() {
    std::tuple<int, int> foo{1,2};
    std::tuple<double> bar = auto_slice(foo);
    
    std::cout << std::get<0>(bar) << '\n';
    
    std::tuple<char> x{'a'};
    auto_slice(foo) = x;
    std::cout << (char)std::get<0>(foo) << '\n';
    
    auto_slice(bar) = auto_slice(foo);
    std::cout << std::get<0>(bar) << '\n';
}