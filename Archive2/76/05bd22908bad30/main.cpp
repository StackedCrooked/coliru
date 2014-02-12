#include <vector>

class X{
public:
  explicit X(int){}
  X(X&&) = default;
  X(const X&) = delete;
  void operator = (const X&) = delete;
};

int main() {
    std::vector<X> xs;
    xs.emplace_back(0);
    xs.emplace_back(1);
    xs.emplace_back(2);
    xs.emplace_back(3);

    return 0;
}