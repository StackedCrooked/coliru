#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

class my_error : public std::runtime_error {
 public:
  explicit my_error(const std::string& e) : runtime_error(e) {}
};

template <class T1>
std::string format(const T1& p1) {
    std::ostringstream stream;
    stream << p1;
    return stream.str();    
}

template <class T1, class T2>
std::string format(const T1& p1, const T2& p2) {
   std::ostringstream stream;
   stream << p1;
   stream << p2;
  return stream.str();
}

template <class T1, class T2, class T3>
std::string format(const T1& p1, const T2& p2, const T3& p3) {
   std::ostringstream stream;
   stream << p1;
   stream << p2;
   stream << p3;
  return stream.str();
}

template <class T1, class T2, class T3, class T4>
std::string format(const T1& p1, const T2& p2, const T3& p3, const T4& p4) {
   std::ostringstream stream;
   stream << p1;
   stream << p2;
   stream << p3;
   stream << p4;
  return stream.str();
}

template <class T1, class T2, class T3, class T4, class T5>
std::string format(const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5) {
   std::ostringstream stream;
   stream << p1;
   stream << p2;
   stream << p3;
   stream << p4;
   stream << p5;
  return stream.str();
}

int main() {
  try {
    const int cols = 3;
    const int rows = 4;
    throw my_error(
      format("Number of columns in A (", cols, ") must match number of rows in B (", rows, ")"));
  }
  catch (const my_error &e) {
    std::cout << e.what() << "\n";
  }
  return 0;
}