#include <unordered_map>
#include <memory>
#include <iostream>
class Foo {
public:
~Foo() { std::cout << "Foo destroyed" << std::endl; }
};
typedef std::unique_ptr<Foo> FooPtr;

// First attempt; this did _not_ compile
//typedef std::unordered_map<int, FooPtr> IntToFooMap;

// Second attempt; this _did_ compile
typedef std::unordered_map<int, const FooPtr &> IntToFooMap;
int main()
{
    IntToFooMap m {
        { 41, FooPtr(new Foo()) }
    };
    
  std::cout << "main() ended" << std::endl;
  return 0;
}