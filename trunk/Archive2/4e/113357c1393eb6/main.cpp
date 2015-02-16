#include <memory>
#include <iostream>
#include <functional>

template <typename>
struct S
{
  S()
  {
    std::cout << "S::S()[" << this << "]" << std::endl;
  }

  std::string y_{"hi mate"};
  int x_;
  std::function<void(int*)> del_{[this](int *ptr)
  {
    std::cout << "Deleting ptr[" << ptr << "] this[" << this << "] this->y_[" << this->y_ << "]" << std::endl;
  }};
  std::unique_ptr<decltype(x_), decltype(del_)> unique_{&x_, del_};
};

int main()
{
  S<int> s;
}