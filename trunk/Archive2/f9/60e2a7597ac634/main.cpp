#include <type_traits>
#include <utility>

template<bool kValue, typename...>
class DependentBool : public std::integral_constant<bool, kValue> {
};

template <unsigned int mask_>
struct Foo {
  template <class PointerType>
  static typename std::enable_if<DependentBool<mask_ == 0u, PointerType>::value, void>::type bar(PointerType* data) { }

  template <class PointerType, unsigned int m_ = mask_>
  static typename std::enable_if< DependentBool<m_ == 1u, PointerType>::value, void>::type bar(PointerType* data) { }

  template <class PointerType, unsigned int m_ = mask_>
  static typename std::enable_if< DependentBool<m_ == 2u, PointerType>::value, void>::type bar(PointerType* data) { }
};


int main(int argc,char*argv[]) {
  unsigned int x;
  Foo<0>::bar(&x);
  return 0;
}