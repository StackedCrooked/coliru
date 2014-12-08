#include <type_traits>
#include <utility>

using std::forward;
using std::declval;

template <class> struct result_of;
 
namespace detail {
template <class F, class... Args>
inline auto INVOKE(F&& f, Args&&... args) ->
    decltype(forward<F>(f)(forward<Args>(args)...)) {
      return forward<F>(f)(forward<Args>(args)...);
}
 
template <class Base, class T, class Derived>
inline auto INVOKE(T Base::*&& pmd, Derived&& ref) ->
    decltype(forward<Derived>(ref).*pmd) {
      return forward<Derived>(ref).*pmd;
}
 
template <class PMD, class Pointer>
inline auto INVOKE(PMD&& pmd, Pointer&& ptr) ->
    decltype((*forward<Pointer>(ptr)).*forward<PMD>(pmd)) {
      return (*forward<Pointer>(ptr)).*forward<PMD>(pmd);
}
 
template <class Base, class T, class Derived, class... Args>
inline auto INVOKE(T Base::*&& pmf, Derived&& ref, Args&&... args) ->
    decltype((forward<Derived>(ref).*pmf)(forward<Args>(args)...)) {
      return (forward<Derived>(ref).*pmf)(forward<Args>(args)...);
}
 
template <class PMF, class Pointer, class... Args>
inline auto INVOKE(PMF&& pmf, Pointer&& ptr, Args&&... args) ->
    decltype(((*forward<Pointer>(ptr)).*forward<PMF>(pmf))(forward<Args>(args)...)) {
      return ((*forward<Pointer>(ptr)).*forward<PMF>(pmf))(forward<Args>(args)...);
}
} // namespace detail
 
// C++11 implementation:
template <class F, class... ArgTypes>
struct result_of<F(ArgTypes...)> {
    using type = decltype(detail::INVOKE(
        declval<F>(), declval<ArgTypes>()...
    ));
};

struct A {
    void foo() {}
};

const auto foo = &A::foo;
static_assert(std::is_void<result_of<decltype(foo)(A)>::type>(), "Failure.");
