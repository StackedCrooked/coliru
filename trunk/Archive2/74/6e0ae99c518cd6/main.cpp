//#include <initializer_list>
#include<array>
template<class T, int Length>
class Point
{
  public:
    Point(std::array<T, Length> init)
    {
//      static_assert(init.size() == Length, "Wrong number of dimensions");
    }
};

int main()
{
  Point<int, 3> q({1,2,3}); //ok
//  Point<int, 3> q2({1,2,3,4}); //compile error (good!)
  Point<int, 3> q2({1,2}); // ok, compiles, same as {1,2,0}, feature?
  return 0;
}
