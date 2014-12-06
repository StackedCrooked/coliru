#include <map>

template<class Key, template<class, class, class, class> class Map = std::map>
class MyClass {
};

int main() {
  MyClass<int> mc;
}