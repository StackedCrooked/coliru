#include <stdio.h>
#include <memory>

    struct A{
      int c_ = 10;
      int add(int a, int b){
        return a + b + c_;
      }
    };
    template<class T>
    std::weak_ptr<A> weak( std::shared_ptr<T> const& sp ) { return {sp}; }

    int main(){
      auto p_a = std::make_shared<A>();
      std::function<int()> f = [w_a = weak(p_a)]() {
        if (auto p_a = w_a.lock())
          return p_a->add(1,1);
        throw w_a;
      };
      printf("%i\n", f()); // yields "12" (1 + 1 + 10)
      p_a.reset();
      try {
        printf("%i\n", f()); // yields derpy numbers, no errors thrown.
      } catch( std::weak_ptr<A> wp ) {
        printf("object deleted\n");
      }
    }