#include <unordered_map>
#include <memory>
#include <cstddef>
#include <iostream>

template<typename T>
class TestAllocator;

template<>
class TestAllocator<void>
{
public:
  typedef void * pointer;
  typedef const void * const_pointer;
  typedef void value_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  //typedef T & reference; not possible for void
  //typedef const T & const_reference; not possible for void
  
  template<typename U>
  struct rebind
  {
    typedef TestAllocator<U> other;  
  };
};

template<typename T>
class TestAllocator
{
public:
  typedef T * pointer;
  typedef const T * const_pointer;
  typedef T & reference;
  typedef const T & const_reference;
  typedef T value_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  
  template<typename U>
  struct rebind
  {
    typedef TestAllocator<U> other;  
  };
  
  TestAllocator() { }
  template<typename U>
  TestAllocator(const TestAllocator<U> &) { }
  
  pointer allocate(int n, pointer =0) { return new T[n]; }
  void deallocate(pointer p, size_t) { delete[] p; }
  pointer address(reference x) { return &x; } // hack! should be std::addressof(x);
  void construct(pointer p, const_reference val) { new (p) value_type(val); }
  void destroy(pointer p) { p->~value_type(); }
};

struct Foo
{
    int a, b;
    bool operator <(const Foo &r) const
    {
        return a < r.a;
    }
};

struct Bar { float a, b; };

struct TrivialHash
{
    size_t operator()(const Foo &a) const
    {
        return a.a;
    }
};

struct TrivialEqual
{
    bool operator()(const Foo &a, const Foo &b) const
    {
        return a.a == b.a;
    }
};

typedef std::unordered_map<
  Foo, Bar,
  TrivialHash,
  TrivialEqual,
  TestAllocator<std::pair<Foo,Bar>>
> TestContainer;

int main()
{
    TestContainer x;
    x.insert(TestContainer::value_type(Foo(), Bar()));
    std::cout << "pass";
    return 0;
}
