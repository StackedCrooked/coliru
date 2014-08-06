#include <functional>
#include <memory>
#include <iostream>
#include <type_traits>
#include <utility>


template<class F>
struct recursive {
private:
  F base;
public:

  template<class... Ts>
  auto operator()(Ts&&... ts) const
  {
    return base(base, std::forward<Ts>(ts)...);
  }

  recursive(recursive const&)=default;
  recursive(recursive&&)=default;
  recursive& operator=(recursive const&)=default;
  recursive& operator=(recursive &&)=default;
  recursive() = delete;
  template<typename L,typename=typename std::enable_if< std::is_convertible<L, F>::value>::type>
  recursive( L&& f ):
    base( std::forward<L>(f) )
  {}
};

template<class T>using decay_t = typename std::decay<T>::type;

template<class F>
recursive<decay_t<F>> recurse( F&& f ) { return std::forward<F>(f); }

auto get_recursive_function(int amt) {
  return recurse( [amt] (auto&& self, int count)->void {
    std::cout << count << std::endl;
    if (count > 0)
      self(self, count - amt);
  });
};

int main() {
  auto f = get_recursive_function(2);
  f(10);
}