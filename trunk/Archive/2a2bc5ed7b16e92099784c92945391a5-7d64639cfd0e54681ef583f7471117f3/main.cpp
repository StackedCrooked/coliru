#include <memory>

struct B {
  virtual ~B() { }
};

class D : public B {
private:
  ~D() { }
};

int main()
{
  std::unique_ptr<B> p(new D);
}