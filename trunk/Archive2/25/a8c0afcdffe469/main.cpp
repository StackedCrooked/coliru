#include <memory>
#include <vector>
#include <functional>
#include <boost/pool/object_pool.hpp>

#include <iostream>

struct Foo {
   Foo(int i) : _i(i) { std::cout << __PRETTY_FUNCTION__ << ' ' << _i << '\n'; }
   static void* operator new(size_t) = delete;
   static void* operator new(size_t count, void *p)
   {
       return ::operator new(count, p);
   }
   int _i;
 };

 using FooHandle = std::unique_ptr<Foo, std::function<void(Foo *)>>;

 struct Bar {
    FooHandle addFoo(int i) 
    {
      Foo* ptr = new (_fooPool.malloc()) Foo(i);
      return FooHandle(ptr, std::bind(&boost::object_pool<Foo>::destroy,
                                      &_fooPool, std::placeholders::_1));
    }
    boost::object_pool<Foo> _fooPool;
 };
 
int main()
{
    Bar b;
    b.addFoo(42);
    
    delete(::new Foo(10));
}
