#include <string>
#include <iostream>

template <typename T>
struct func_impl {
static std::string func()
{
      // Do something generically
      return "Generic data";
}
};



template <>
std::string func_impl<bool>::func()
{
      // Handle booleans differently
      return "Boolean data";
}



template<typename T>
struct SpecialType {};

template <typename T>
struct func_impl<SpecialType<T>> {
static std::string func()
{
      // Any "T" of SpecialType<T> should be handled
      return "Special data";
}
};




// Calling code
template <typename T>
std::string process(const T &)
{
      return func_impl<T>::func();
}




int main() {
     int i;
     bool b;
     SpecialType<int> s;
     std::cout << process(i) << ' ' << process(b) << ' ' << process(s) << '\n';
}