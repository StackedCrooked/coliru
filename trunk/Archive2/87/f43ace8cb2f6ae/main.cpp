#include <utility>

class Embed {
 public:
  void embedMethod() { }
};

class Container {
 private:
  Embed embed;
 public:
  void containerMethod() {}
  
  template<typename ...Args, typename R>
  R forward( R (Embed::* function)(Args...), Args &&...args) {
    return (embed.*function)(std::forward<Args>(args)...);
  }
};

int main() {
  Container c;
  c.containerMethod();
  c.forward(&Embed::embedMethod);
}
