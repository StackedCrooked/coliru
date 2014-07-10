#include <unordered_map>
#include <memory>

class Foo {  };
typedef std::unique_ptr<Foo> FooPtr;

// First attempt; this did _not_ compile
typedef std::unordered_map<int, FooPtr> IntToFooMap;

// Second attempt; this _did_ compile
//typedef std::unordered_map<int, const FooPtr &> IntToFooMap;
int main()
{
  IntToFooMap test1;
  test1[1] = std::make_unique<Foo>();
  return 0;
}