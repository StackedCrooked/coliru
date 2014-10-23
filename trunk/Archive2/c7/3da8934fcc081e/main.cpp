#include <memory>
#include <iostream>

struct Bar {
    void hello() { std::cout << "Hello\n"; }
};

struct Foo {
  std::unique_ptr<Bar> bar_{};
  void setInstance(std::unique_ptr<Bar> bar) { bar_ = std::move(bar); }
};

int main() {
    auto foo = Foo{};
    foo.setInstance(std::make_unique<Bar>());
    
    
    auto bar = std::make_unique<Bar>();
    foo.setInstance(std::move(bar));
    
    foo.bar_->hello();
}
