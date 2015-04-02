#include <memory>
#include <iostream>

enum class should_delete {
  yes,
  no,
};

template<class T, class Deleter= std::default_delete<T>>
struct maybe_delete:Deleter {
  should_delete choice = should_delete::yes;
  void operator()(T* t){
    if (choice!=should_delete::no)
      delete t;
  }
  maybe_delete() = default;
  template<class...Args>
  maybe_delete(should_delete c,Args&&...args):
    Deleter(std::forward<Args>(args)...),
    choice(c)
  {}
  maybe_delete(maybe_delete const&)=default;
  maybe_delete(maybe_delete&& o):Deleter(std::move(o)), choice(o.choice)
  {
    o.choice = should_delete::yes;
  }
};
template<class T>
using maybe_unique_ptr = std::unique_ptr<T, maybe_delete<T>>;

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