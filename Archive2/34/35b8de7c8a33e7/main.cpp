#include <memory>

struct MyClass;

int main() {
  delete (MyClass*)42;
}

struct MyClass
{
  //MyClass's interface
  private:
  ~MyClass() { /* something */ }
  friend struct std::default_delete<MyClass>;
};
