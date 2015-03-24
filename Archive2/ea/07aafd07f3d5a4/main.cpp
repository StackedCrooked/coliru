#include <iostream>

struct one
{
  int size() const { return 1; };
};

struct two
{};

template <typename T>
class has_size
{
private:
  typedef char Yes;
  typedef Yes No[2];
  
  template<typename C> static auto Test(void*)
    -> decltype(size_t{std::declval<C const>().size()}, Yes{});
  
  template<typename> static No& Test(...);
  
public:
  static bool const value = sizeof(Test<T>(0)) == sizeof(Yes);
};

int main()
{
  std::cerr << has_size<one>::value << '\n';
  std::cerr << has_size<two>::value << '\n';
}
