#include <iostream>
#include <utility>
#include <functional>
#include <memory>

template<typename F>
class SafeCallback {
public:
  template<class O>
  using compatible=std::enable_if_t<std::is_convertible<O,F>::value>;
  template<class T, class=compatible<T>>
  SafeCallback(std::shared_ptr<bool> is_valid, T&& callback):
    is_valid_(is_valid),
    callback_(std::forward<T>(callback))
  {}

  template <class ...Arg>
  void operator()(Arg&&... parameters) {
    if ((*is_valid_) == true) {
      callback_(std::forward<Arg>(parameters)...);
    }
  }
  template <class ...Arg>
  void operator()(Arg&&... parameters)const {
    if ((*is_valid_) == true) {
      callback_(std::forward<Arg>(parameters)...);
    }
  }
  SafeCallback(SafeCallback const& o)=default;
  SafeCallback(SafeCallback && o)=default;
  template<class O, class=compatible<O const&>>
  SafeCallback(SafeCallback<O> const& o):
    is_valid_(o.is_valid_),
    callback_(o.callback_)
  {}
  template<class O, class=compatible<O>>
  SafeCallback(SafeCallback<O> && o):
    is_valid_(std::move(o.is_valid_)),
    callback_(std::move(o.callback_))
  {}
private:
  std::shared_ptr<bool> is_valid_;
  F callback_;
};


template<class F, class F_v=std::decay_t<F>>
SafeCallback<F_v>
makeSafe(std::shared_ptr<bool> is_valid, F&& callback) {
  return SafeCallback<F_v>(is_valid, std::forward<F>(callback));
}
int f(int x){std::cout << x << "\n";return x;}

int main() {
    auto flag = std::make_shared<bool>(true);
    auto f_safe = makeSafe( flag, f );
    f_safe(3);
    *flag = false;
    f_safe(2);
    *flag = true;
    f_safe(1);
}