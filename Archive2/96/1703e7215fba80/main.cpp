#include <map>

template<class Key, template<class, class, class, class> class Map = std::map>
class MyClass {
};

template<class Key, template<class...> class Map = std::map>
class MyClass2 {
};

int main() {
  MyClass<int> mc;
  MyClass2<int> mc2;
}