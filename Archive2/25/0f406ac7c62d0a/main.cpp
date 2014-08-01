#include <functional>
#include <memory>
#include <iostream>
#include <type_traits>
#include <utility>

template<class Sig>
struct recursive;
template<class R, class... As>
struct recursive< R(As...) > {
  using base_type = std::function<R(recursive, As...)>;
  typedef R(*ptr_type)(recursive, As...);
private:
  std::shared_ptr< base_type > base;
public:

  template<typename...Ts>
  auto operator()(Ts&&... ts) const
  -> typename std::result_of< ptr_type( recursive, Ts... ) >::type
  {
    return (*base)(*this, std::forward<Ts>(ts)...);
  }

  recursive(recursive const&)=default;
  recursive(recursive&&)=default;
  recursive& operator=(recursive const&)=default;
  recursive& operator=(recursive &&)=default;
  recursive() = default;
  template<typename L, typename=typename std::result_of< L(recursive, As...) >::type>
  explicit recursive( L&& f ):
    base( std::make_shared<base_type>(std::forward<L>(f)))
  {}
  explicit operator bool() const { return base && *base; }
};

    std::function<void (int)> get_recursive_function() {
      auto f =
        [] (auto&& self, int count) {
          std::cout << count << std::endl;

          if (count > 0) {
            self(count - 1);
          }
        };
      return recursive< void(int) >( f );
    };

    int main() {
      auto f = get_recursive_function();
      f(10);
    }