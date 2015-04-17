#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

class my_error : public std::runtime_error {
 public:
  explicit my_error(const std::string& e) : runtime_error(e) {}
};

class format {
 public:
  format() {}
  operator std::string() const {
    return stream.str();
  }

  template <class T>
  friend const format& operator<<(const format& f, const T& data) {
    const_cast<format&>(f).stream << data;
    return f;
  }

 private:
  std::ostringstream stream;
};

int main() {
  try {
    const int cols = 3;
    const int rows = 4;
    throw my_error(
      format() << "Number of columns in A (" << cols
      << ") must match number of rows in B (" << rows << ")");
  }
  catch (const my_error &e) {
    std::cout << e.what() << "\n";
  }
  return 0;
}
