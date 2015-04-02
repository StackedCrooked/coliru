#include <memory>
#include <iostream>

enum class should_delete {
  yes,
  no,
};
struct maybe_delete {
  should_delete choice = should_delete::yes;
  template<class T>
  void operator()(T* t){
    if (choice!=should_delete::no)
      delete t;
  }
  maybe_delete() = default;
  maybe_delete(should_delete c):choice(c) {}
  maybe_delete(maybe_delete const&)=default;
  // move in terms of copy, then clear state to default:
  maybe_delete(maybe_delete&& o):maybe_delete(o){
    o.choice = should_delete::yes;
  }
};
template<class T>
using maybe_unique_ptr = std::unique_ptr<T, maybe_delete>;

struct noisy {
    ~noisy(){std::cout << "bang!\n";}
};
int main() {
    std::cout << "one:\n";
    {
        maybe_unique_ptr<noisy> x(new noisy());
    }
    std::cout << "two:\n";
    {
        maybe_unique_ptr<noisy> x(new noisy(), should_delete::no);
    }
    std::cout << "three:\n";
    {
        maybe_unique_ptr<noisy> x(new noisy());
    }
}