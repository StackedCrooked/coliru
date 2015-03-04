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

struct FooDeleter
{
    FooDeleter(boost::object_pool<Foo>& pool)
    : pool(&pool)
    {}
    
    void operator()(Foo *p)
    {
        pool->destroy(p);
    }
    boost::object_pool<Foo> *pool;
};

using FooHandle = std::unique_ptr<Foo, FooDeleter>;

struct Bar {
    FooHandle addFoo(int i) 
    {
      Foo* ptr = ::new (_fooPool.malloc()) Foo(i);
      return FooHandle(ptr, FooDeleter(_fooPool));
    }
    boost::object_pool<Foo> _fooPool;
};
 
int main()
{
    Bar b;
    b.addFoo(42);
    
    delete(::new Foo(10));
}
