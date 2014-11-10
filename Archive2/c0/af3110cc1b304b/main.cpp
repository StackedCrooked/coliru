#include <functional>
#include <iostream>
#include <vector>

template <typename InType, typename OutType>
class Pipe {
public:
  Pipe(std::function<OutType(InType)> transform) :
    transform_(std::move(transform)) {}

  // For lvalues, return reference to *this for chaining.
  Pipe& addListener(std::function<void(OutType)> f) & {
    listeners_.push_back(std::move(f));
    return *this;
  }

  // For rvalues, return *this by value for chaining.
  Pipe addListener(std::function<void(OutType)> f) && {
    listeners_.push_back(std::move(f));
    return std::move(*this);
  }

  void operator() (InType value) {
    const auto outValue = transform_(std::move(value));
    for (auto& listener : listeners_) {
      listener(outValue);
    }
  }

private:
  std::function<OutType(InType)> transform_;
  std::vector<std::function<void(OutType)>> listeners_;
};

struct printer {
  template <typename T>
  void operator()(const T& t) {
    std::cout << t << '\n';
  }
};

int main() {
  auto pipe = Pipe<int, std::string>{
    [](int i){ return std::to_string(i); }
  }.addListener(printer{}).addListener(
    Pipe<std::string,std::string>{
      [](const std::string& s){ return s + ' ' + s; }
    }.addListener(printer{})
  );
  pipe(42);
  pipe(13);
}
