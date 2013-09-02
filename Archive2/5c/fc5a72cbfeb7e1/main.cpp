#include <iostream>
#include <utility>

template<typename T>
class Point {
  private:
    T px, py;
  public:
    Point(T x, T y): px(x), py(y) {
      std::cout << "created " << x << ":" << y <<std::endl;
    };
    T x() const { return px; };
    T y() const { return py; };
};

class PointScreen: public Point<int> {
  public:
    // template version: "forwards" all arguments to ctors of the base class
    template < typename... Args >
    PointScreen(Args&&... args)
    : Point(std::forward<Args>(args)...)
    {}
    
    // non-template version
    PointScreen(int x, int y)
    : Point(x, y)
    {}
};

// definitions from above      
int main() {
  std::cout << PointScreen(100, 100).x() << std::endl;
  return 0;
}
