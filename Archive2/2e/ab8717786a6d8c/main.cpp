#include <iostream>
#include <type_traits>
#include <utility>

// Library code
namespace lib {
  namespace detail {
    // Simple trait that computes the inverse of std::is_same
    template <typename, typename>
    struct is_different : std::true_type {};
    template <typename T>
    struct is_different<T, T> : std::false_type {};

    // The ellipsis conversion is worse than any other
    // conversion, so overload resolution will choose
    // this declaration of foo only if there is no
    // result from ADL.
    struct tag;
    tag foo(...);

    // Trait that determines if ADL for foo(T) succeeds.
    template <typename T>
    using has_adl_foo =
      is_different<tag,decltype(foo(std::declval<T>()))>;

    // Fallback, used only if ADL fails.
    template <typename T>
    typename std::enable_if<!has_adl_foo<T>::value>::type
    impl(T&&) {
      std::cout << "Fallback\n";
    }

    // Dispatch to foo found by ADL.
    template <typename T>
    typename std::enable_if<has_adl_foo<T>::value,
      decltype(foo(std::declval<T>()))
    >::type
    impl(T&& t) {
      return foo(std::forward<T>(t));
    }
  } // namespace detail

  template <typename T>
  auto foo(T&& t) ->
    decltype(detail::impl(std::forward<T>(t))) {
      return detail::impl(std::forward<T>(t));
  }
} // namespace lib

// User code
struct UserType {};
struct DerivedUserType : UserType {};

void foo(const UserType&) {
  std::cout << "User extension\n";
}

int main() {
  std::cout << "non-user type: ";
  lib::foo(42);

  std::cout << "UserType: ";
  lib::foo(UserType{});

  std::cout << "DerivedUserType: ";
  lib::foo(DerivedUserType{});
}
