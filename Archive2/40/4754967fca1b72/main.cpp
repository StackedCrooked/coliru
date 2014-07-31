#include <iostream>
#include <memory>

namespace util {
  namespace details {
    namespace fake_std {
      template<typename T, typename... Args>
      std::unique_ptr<T> make_unique(Args &&... args, ...) { // super hackish
        std::cerr << "backup implementation";
        return std::unique_ptr<T> (new T (std::forward<Args>(args)...));
      }
    }
    using namespace std;
    using namespace fake_std;
  }

  using details::make_unique;
}

int main () {
  using util::make_unique;

  make_unique<int> (0); // will call std::make_unique if available
}