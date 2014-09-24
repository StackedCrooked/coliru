#include <iostream>
#include <memory>
#include <type_traits>

class InitableKey {
private:
  friend class Initable;
  InitableKey() {}
public:

  // Movable but not copyable
  InitableKey(InitableKey&&) = default;
  InitableKey& operator=(InitableKey&&) = default;
  InitableKey(const InitableKey&) = delete;
  InitableKey& operator=(const InitableKey&) = delete;
};

class Initable {
 private:
   
   static void deleter(Initable* aptr) { aptr->terminate(); delete aptr; };
 public:
  Initable(InitableKey&& key) { (void) key; }  // Suppressed unused parameter warning.
  virtual ~Initable() {}
  virtual void terminate() = 0;

  template<typename T, typename... Ts>
  static std::unique_ptr<T, decltype(&deleter)> make_initable(Ts&&... args) {
    static_assert(std::is_base_of<Initable, T>::value,  "Can only be used to create Initable types.");
    return std::unique_ptr<T, decltype(&deleter)>(new T(std::forward<Ts>(args)..., InitableKey{}), &deleter);
  }
  
};

class B : public Initable {
 public:
  B(InitableKey&& key) : Initable(std::move(key)) {}
  void terminate() override { std::cout << "terminate\n"; }
};

/*
class Bad {
  public:
  Bad(InitableKey&& key) {
    B b(std::move(key));  // Try to create a B witout using make_initable!
  }
};
*/


class BadInitable : public Initable {
  public:
  BadInitable(InitableKey&& key) : Initable(std::move(key)) {
    B b(std::move(key));  // Try to create a B witout using make_initable!
  }
  void terminate() override { std::cout << "terminate BadInitable\n"; }
};


int main() {
  std::shared_ptr<B> b = Initable::make_initable<B>();
//  auto bad = Initable::make_initable<Bad>();
  auto bad = Initable::make_initable<BadInitable>();
}