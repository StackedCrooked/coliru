#include <utility>
#include <type_traits>
#include <iostream>
#include <typeinfo>

#define WINAPI

template<class Sig>
struct is_rvalue_function : std::false_type {};
template<class R, class...Args>
struct is_rvalue_function< R(*&&)(Args...) > : std::true_type {};
//template<class R, class...Args>
//struct is_rvalue_function< R(*&)(Args...) > : std::false_type {};

namespace details {
  template <typename RET_TYPE, typename...ARGs>
  void* fnPtrToVoidPtr(std::true_type, RET_TYPE(WINAPI * pOriginalFunction)(ARGs...)) {
    return (void*)pOriginalFunction;
  }
  // Cast a function pointer that is referencable to a void *&
  template <typename RET_TYPE, typename...ARGs>
  void*& fnPtrToVoidPtr(std::false_type, RET_TYPE(WINAPI*& pOriginalFunction)(ARGs...)) {
    return (void*&)pOriginalFunction;
  }

}
template<class T>
auto fnPtrToVoidPtr(T&& t)
-> decltype(
  details::fnPtrToVoidPtr(
    std::is_rvalue_reference<T&&>{}, std::forward<T>(t)
  )
) {
  return
  details::fnPtrToVoidPtr(
    std::is_rvalue_reference<T&&>{}, std::forward<T>(t)
  );
}

void foo() {}
auto* pfoo = foo;


int main() {
    fnPtrToVoidPtr(&foo);// = nullptr; // fails
    fnPtrToVoidPtr(pfoo) = nullptr;
}