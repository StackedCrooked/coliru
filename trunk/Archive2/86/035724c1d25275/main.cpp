#include <iostream>
#include <string>
#include <functional>
#include <type_traits>
#include <utility>

namespace detail {
  template<class T, bool = std::is_class<typename std::remove_reference<T>::type> {}>
  struct Lazy {
    Lazy (T& ref) : _read ([&]()->T&{ return ref; }) { }

    template<class Fn>
    Lazy (Fn f) : _read (f) {}

    T get () const {
      return _read ();
    }

    template<class U>
    auto operator+ (Lazy<U> const& rhs) -> Lazy<decltype (std::declval<T> () + rhs.get ())> {
      auto c1 = _read;
      auto c2 = rhs._read;
      return {
        [=]{ return c1() + c2 (); }
      };
    }

    template<class U>
    auto operator* (U val) -> Lazy<decltype (std::declval<T> () + val)> {
      auto c1 = _read;
      return {
        [=]{ return c1() * val; }
      };
    }

    std::function<T()> _read;
  };

  template<class T>
  struct Lazy<T, true> : Lazy<T, false> {
    using Lazy<T, false>::Lazy;
    using value_type = typename std::remove_reference<T>::type;

    template<class R, class... Args>
    auto call (R(value_type::*mfptr)(Args...) const, Args... args) -> Lazy<R> {
      auto cpy = this->_read;
      return { [=]()->R{ return (cpy ().*mfptr) (args...); } };  
    }
  };

}

template<class T>
using Lazy = detail::Lazy<T>;

template<class T>
Lazy<T&> lazy (T& ref) { return { ref }; }

struct A {
  std::string data;
  Lazy<std::string&>  alias      = lazy (data);
  Lazy<unsigned long> length     = lazy (data).call (&std::string::size);
  Lazy<unsigned long> double_len = length * 2;
};

int main () {
  A a;

  a.data = "abc";
  std::cout << a.data << " " << a.length.get () << " " << a.double_len.get () << std::endl;

  a.alias.get () = "hello world";
  std::cout << a.data << " " << a.length.get () << " " << a.double_len.get () << std::endl;
}