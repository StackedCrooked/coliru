#include <memory>

struct Foo { };

class Bar {
 private:
  std::unique_ptr<Foo> foo_;
 protected:
  ~Bar() = default;
  Bar() = default;
  Bar(Bar&&) = default;
  Bar& operator=(Bar&&) = default;
};

class Widget : public Bar {
};

int main() {
  Widget w1;
  Widget w2 = std::move(w1);
  Widget w3;
  w3 = std::move(w1);
 }
