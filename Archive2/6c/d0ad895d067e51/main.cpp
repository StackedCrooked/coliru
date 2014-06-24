#include <map>
#include <stdio.h>

enum class Direction
{
  UP=-1,
  DOWN=1
};

template <Direction dir>
struct Comparator
{
  bool operator()(int lhs, int rhs) const
  {
    return lhs<rhs; // Comparison should be based on dir
                    // but let's not even use dir for now
  }
};

template <Direction dir>
using IntToIntMap=std::map<int, int, Comparator<dir>>;

template <Direction dir>
void TestFunc()
{
  using TheMap=IntToIntMap<dir>; // TheMap should be a synonym for
                                 // IntToIntMap<dir>

  typename IntToIntMap<dir>::value_type value1; // This compiles
  typename TheMap::value_type value2;           // This does not (???)
}

int main()
{
  TestFunc<Direction::UP>();
  printf("Success!\n");
}
