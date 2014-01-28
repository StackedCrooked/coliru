#include <functional>

struct X
{
  X(int){}
};

int main()
{
  std::function<void(X&)> f=&X::~X;
}