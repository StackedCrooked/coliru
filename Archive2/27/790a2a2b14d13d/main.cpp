#include <utility>
#include <iostream>
#include <type_traits>

    template<class T>using type=T;
    
    template<class Sig, Sig* func>
    struct super_func;
    template<class R, class...Args, R(*func)(Args...)>
    struct super_func<R(Args...), func> {
      using Sig = R(Args...);
      using pSig = Sig*;
      template<class R2, class...Args2, class=std::enable_if_t<
        std::is_convertible<
          std::result_of_t<pSig(Args2...)>,
          R2
        >{}
        && !std::is_same<R2, void>{}
      >>
      constexpr operator type<R2(Args2...)>*() const {
        return [](Args2...args)->R2{
          return func(std::forward<Args2>(args)...);
        };
      }
      template<class...Args2, class=std::enable_if_t<
        std::is_same<
          std::result_of_t<pSig(Args2...)>,
          R
        >{}
      >>
      constexpr operator type<void(Args2...)>*() const {
        return [](Args2...args)->void{
          func(std::forward<Args2>(args)...);
        };
      }
      constexpr operator pSig() const {
        return func;
      }
      constexpr R operator()(Args...args)const{
        return func(std::forward<Args>(args)...);
      }
    };

void foo() {}
int bar(){ return 3; }

int main() {
    super_func< decltype(foo), &foo > super_foo;
    super_foo();
    super_func< decltype(bar), &bar > super_bar;
    type< double() >* pbar2 = super_bar;
    
    std::cout << std::is_convertible<int, void>{} << '\n';
    std::cout << pbar2() << '\n';
}