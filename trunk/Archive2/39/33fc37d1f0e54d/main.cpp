#include <iostream>
#include <vector>

struct Noisy {
  Noisy() { std::cout << "Noisy()\n"; }
  Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)\n"; }
  Noisy(Noisy&&) noexcept { std::cout << "Noisy(Noisy&&)\n"; }
  Noisy& operator=(const Noisy&) { std::cout << "operator=(const Noisy&)\n"; return *this;}
  Noisy& operator=(Noisy&&) noexcept { std::cout << "operator=(Noisy&&)\n"; return *this;}
};

class Widget {
public:
  using DataType = std::vector<Noisy>;
  DataType& data() &  { return values; }
  DataType  data() && { return std::move(values); }
  
  Widget() : values(1) {}
private:
  DataType values;
};

Widget makeWidget() {
 return Widget{};
}

int main() {
  Widget w;
  
  std::cout << "auto vals1 = w.data()\n";
  auto vals1 = w.data();
  
  std::cout << "auto vals2 = makeWidget().data()\n";
  auto vals2 = makeWidget().data();
}
