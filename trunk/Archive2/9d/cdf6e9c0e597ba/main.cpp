#include <memory>
#include <unordered_map>

class Foo {
    virtual void bar() {
        
    }
};

typedef std::unique_ptr<Foo> FooPtr;

typedef std::unordered_map<int, FooPtr> IntToFooMap;

int main()
{
    IntToFooMap map {
        { 1, FooPtr(new Foo()) }
    };
}
