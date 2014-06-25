#include <iostream>
    
class C {
public:
  static const void *noop;
};
    
const void* C::noop = (const void*) 0x1;
    
auto main() -> int {
  std::cout << C::noop << std::endl;
  return 0;
}