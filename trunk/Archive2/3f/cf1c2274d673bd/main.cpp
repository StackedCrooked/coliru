#include <iostream>
#include <memory>

class Initable {
 private:
   static void deleter(Initable* aptr) { aptr->terminate(); delete aptr; };
 public:
  virtual ~Initable() {}
  virtual void terminate() = 0;

  template<typename T, typename... Ts>
  static std::unique_ptr<T, decltype(&deleter)> make_initable(Ts&&... args) {
    return std::unique_ptr<T, decltype(&deleter)>(new T(std::forward<Ts>(args)...), &deleter);
  }
  
};

class B : public Initable {
 private:
  friend class Initable;
 protected:
  B() : Initable() {}
 public:
  void terminate() override { std::cout << "terminate\n"; }
};


int main() {
  auto b = Initable::make_initable<B>();
}