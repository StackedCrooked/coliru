#include <utility>
#include <iostream>

template<class F, F&> class compose;

template<class R, class... Args, R(&f)(Args...)>
class compose<R(Args...), f> {
  public:
    template<class... Ts>
    compose (Ts&&... args)
      : value (f (std::forward<Ts> (args)...) )
    { }

    operator R & ()       { return value; }
    operator R const& () const { return value; }

  private:
    R value;
};

int g (int x) {
  return x * x;
}

void f (compose<int(int), g> x = 10) {
  std::cerr << "x = " << x << ";\n";
}

int main () {
  f (7);
  f ();
}