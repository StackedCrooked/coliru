 #include <iostream>
 #include <type_traits>

 int main()
 {
     std::cout << std::is_same<int, unsigned int>::value << "\n"; // false
     return 0;
 }