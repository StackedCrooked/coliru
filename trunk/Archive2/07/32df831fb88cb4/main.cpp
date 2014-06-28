#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

namespace detail {
template<bool>
struct helper {
  template<class FN1, class FN2, class... Args>
  static auto fire(FN1 &&fn1, FN2 &&, Args&&... args) ->
  decltype(std::bind(std::forward<FN1>(fn1), std::forward<Args>(args)...)()) {
    return std::bind(std::forward<FN1>(fn1), std::forward<Args>(args)...)();
  }
};        

template<>
struct helper<false> {
  template<class FN1, class FN2, class... Args>
  static auto fire(FN1 &&, FN2 &&fn2, Args&&... args) ->
  decltype(std::bind(std::forward<FN2>(fn2), std::forward<Args>(args)...)()) {
    return std::bind(std::forward<FN2>(fn2), std::forward<Args>(args)...)();
  }
};        
}

template<bool cond, class FN1, class FN2, class... Args>
auto if_else(FN1 &&fn1, FN2 &&fn2, Args&&... args) ->
  decltype(detail::helper<cond>::fire(std::forward<FN1>(fn1), std::forward<FN2>(fn2), std::forward<Args>(args)...)) {
    return detail::helper<cond>::fire(std::forward<FN1>(fn1), std::forward<FN2>(fn2), std::forward<Args>(args)...);
}

// ------------------------------------------------------------------------------------------------------------

struct A {
    int id = 4;
};

struct B : A {
    int h = 900;
};

class Test{
int fn1(B &a){
    std::cout << "fn1 " << a.h;
    return a.h;
};

int fn2(A &a){
    std::cout << "fn2 " << a.id;
    a.id = 9;
    return a.id;
};


public:
    template<bool do_it>
    void go(){
        
        auto data = if_else<do_it>([]{ return B(); }, []{ return A(); });
        std::cout << std::is_same<decltype(data), A>::value << ' ';
        std::cout << if_else<do_it>(&Test::fn1, &Test::fn2, this, data) << '\n';
    }
};

int main(){
    Test().template go<true>();
    Test().template go<false>();
}

