#include <exception>

struct E : std::nested_exception { E(int) {} };

int main() {
 try {
  std::throw_with_nested(E(42));
  return 0;
 }
 catch (E&) {
 }
}