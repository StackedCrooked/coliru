#include <memory>

template <typename _Ty>
class Foo
{
public:
  using allocator_type = typename _Ty::allocator_type;
};

template <typename T>
class Foo<T*>
{
public:
  using allocator_type = typename T::allocator_type;
};

template <typename _Ty, typename _Alloc = std::allocator<_Ty>>
class Bar
{
public:
  using allocator_type = _Alloc;

  Foo<Bar*> foo;
};

int main(void)
{
  Foo<Bar<int>> x;
}