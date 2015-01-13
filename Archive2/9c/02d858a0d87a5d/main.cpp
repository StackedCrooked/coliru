#include <utility>

class A
{
public:
  A(int i, double d) : i(i), d(d) {}
private:
  int i;
  double d;
};

class B
{
public:
  template<typename... ArgTypes>
  B(ArgTypes&&... list_of_args) : a(std::forward<ArgTypes>(list_of_args)...)
  {
    // do something here
  }
private:
  A a;
};

int main()
{
  B b(1, 3.14);
}
