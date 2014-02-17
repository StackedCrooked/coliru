#include <iostream>
#include <unordered_map>

struct Point
{
  Point(int px, int py) : x(px), y(py) {}
  int x,y;

  bool operator==(const Point &other) const
  { return (x == other.x
            && x == other.x);
  }
};

namespace std {
  template <>
  struct hash<Point>
  {
    std::size_t operator()(const Point& k) const
    {
      return (k.x + k.y);
    }
  };
}
int main()
{
   std::unordered_map<Point,std::string> mmap = {
    { {0,1}, "example"},
    { {1,0}, "another"}
   };   
   std::cout << mmap.size() << std::endl;   // outputs 2
   
   std::unordered_map<Point,std::string> mmap2 = {
    { {0,1}, "example"},
    { {0,1}, "another"}
   };   
   std::cout << mmap2.size() << std::endl;   // outputs 1
   return 0;
}