#include <functional>
#include <memory>
#include <iostream>
#include <type_traits>
#include <utility>

struct wrap {};
 
template<class R, class F>
struct recursive {
  using base_type = F;
private:
  F base;
public:

  template<class... Ts>
  R operator()(Ts&&... ts) const
  {
    return base(*this, std::forward<Ts>(ts)...);
  }

  recursive(recursive const&)=default;
  recursive(recursive&&)=default;
  recursive& operator=(recursive const&)=default;
  recursive& operator=(recursive &&)=default;
  recursive() = delete;
  template<typename L>
  recursive( wrap, L&& f ):
    base( std::forward<L>(f) )
  {}
};

template<class T>using decay_t = typename std::decay<T>::type;

template<class R, class F>
recursive<R, decay_t<F>> recurse( F&& f ) { return recursive<R, decay_t<F>>(wrap{}, std::forward<F>(f)); }

    std::function<void (int)> get_recursive_function(int amt) {
      auto f =
        [amt] (auto&& self, int count) {
          std::cout << count << std::endl;

          if (count > 0) {
            self(count - amt);
          }
        };
      return recurse<void>( std::move(f) );
    };

    int main() {
      auto f = get_recursive_function(2);
      f(10);
    }