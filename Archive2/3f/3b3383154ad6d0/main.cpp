#include <memory>
#include <unordered_map>

class Foo {
    virtual void bar() = 0;
};

typedef std::unique_ptr<Foo> FooPtr;

typedef std::unordered_map<int, FooPtr> IntToFooMap;

