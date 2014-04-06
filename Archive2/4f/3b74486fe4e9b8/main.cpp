#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>  // NOLINT
#include <type_traits>
// std::to_string is not provided on Android (without a lot of trouble anyway).
namespace std {
template<typename T>
std::string to_string(const T value) {
  std::ostringstream out;
  out << value;
  return out.str();
}

template<typename T>
std::string to_string(
    const T value, int width,
    typename std::enable_if<std::is_integral<T>::value ||
    std::is_floating_point<T>::value>::type* = 0) {
  std::ostringstream out;
  out << std::setfill('0') << std::setw(width) << value;
  return out.str();
}
}  // namespace std


int main() {
 std::cout << "Integer: " << std::to_string(5) << std::endl;   
 std::cout << "Double: " << std::to_string(5.0) << std::endl;
 std::cout << "String: " << std::to_string("test") << std::endl;
    
 std::cout << "Integer Width: " << std::to_string(5, 5) << std::endl;   
 std::cout << "Double Width: " << std::to_string(5.6, 5) << std::endl;  
 // std::cout << "String Width: " << std::to_string("test", 5) << std::endl;     // Does not compile.
}