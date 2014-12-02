#include <functional>
#include <memory>

struct A {};
struct B {};
struct C {
  std::shared_ptr<A> calc(std::shared_ptr<B> b) { return nullptr; }
};

int main() {
  C c;
  std::function<std::shared_ptr<A>(std::shared_ptr<B>)> x = std::bind(std::mem_fn(&C::calc), &c, std::placeholders::_1);
}