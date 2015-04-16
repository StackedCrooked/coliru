#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

class roots_error : public std::runtime_error {
 public:
  explicit roots_error(const std::string& e) : runtime_error(e) {}
};

class format {
 public:
  format() {}
  operator std::string() {
    return stream.str();
  }

  template <class T>
  friend format&& operator<<(format&& f, const T& data) {
    f.stream << data;
    return std::move(f);
  }

 private:
  std::ostringstream stream;
};

int main() {
  try {
    const int cols = 3;
    const int rows = 4;
    throw roots_error(
      format() << "Number of columns in A (" << cols
      << ") must match number of rows in B (" << rows << ")");
  }
  catch (roots_error &e) {
    std::cout << e.what() << "\n";
  }
  return 0;
}
