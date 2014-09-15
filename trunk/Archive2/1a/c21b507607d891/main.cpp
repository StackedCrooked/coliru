#include <iostream>

class any {
public:
  any() { std::cout << "any()\n"; }
  any(const any &) { std::cout << "any(const any &)\n"; }
  any(any &&)  { std::cout << "any(any&&)\n"; }
  template<typename ValueType> any(const ValueType &) { std::cout << "any<ValueType>(const ValueType&)\n"; }
  template<typename ValueType> any(ValueType &&) { std::cout << "any<ValueType>(ValueType&&)\n"; }
};

int main()
{
    any a;
    const any c;
    
    any f(a);
    any g(c);
}