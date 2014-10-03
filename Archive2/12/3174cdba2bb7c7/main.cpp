#include <boost/optional.hpp>
#include <iostream>

int main() {
 int i = 0;
 auto optional_int = boost::optional<int>();
 float f = 0.0f;
 auto optional_float = boost::optional<float>();
 double d = 0.0;
 auto optional_double = boost::optional<double>(); 
 auto optional_string = boost::optional<std::string>();  
 std::string empty_string = "";
 std::string eight_string = "12345678";
 std::cout << "sizeof int " << sizeof(i) << "\n";
 std::cout << "sizeof boost::optional<int> " << sizeof(optional_int) << "\n";
 std::cout << "sizeof float " << sizeof(f) << "\n";
 std::cout << "sizeof boost::optional<float> " << sizeof(optional_float) << "\n"; 
 std::cout << "sizeof double " << sizeof(d) << "\n";
 std::cout << "sizeof boost::optional<double> " << sizeof(optional_double) << "\n";  
 std::cout << "sizeof boost::optional<string> " << sizeof(optional_string) << "\n";
 std::cout << "sizeof empty string " << sizeof(empty_string) + empty_string.capacity() * sizeof(char) << "\n";
 std::cout << "sizeof eight string " << sizeof(eight_string) + eight_string.capacity() * sizeof(char) << "\n";
}
