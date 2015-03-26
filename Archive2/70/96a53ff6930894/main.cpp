// Example adapted from https://github.com/boostorg/context/tree/boost-1.57.0/example
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <iostream>

#include <boost/context/all.hpp>

template< std::size_t Max, std::size_t Default, std::size_t Min >
class simple_stack_allocator
{
public:
  static std::size_t maximum_stacksize() { return Max;     }
  static std::size_t default_stacksize() { return Default; }
  static std::size_t minimum_stacksize() { return Min;     }

  void* allocate( std::size_t size) const
  {
    void* limit = std::malloc(size);
    if (!limit) throw std::bad_alloc();

    return static_cast<char*>(limit) + size;
  }

  void deallocate(void* vp, std::size_t size) const
  {
    void* limit = static_cast<char*>(vp) - size;
    std::free(limit);
  }
};

typedef simple_stack_allocator<
  8 * 1024 * 1024, // 8MB
  64 * 1024,       // 64kB
  8 * 1024         // 8kB
> stack_allocator;

boost::context::fcontext_t fcm = 0;
boost::context::fcontext_t fc1 = 0;

void f1(intptr_t)
{
  std::cout << "f1: entered" << std::endl;
  boost::context::jump_fcontext(&fc1, fcm, 0, false);
}

int main()
{
  stack_allocator alloc;

  void* base1 = alloc.allocate(stack_allocator::default_stacksize());
  fc1 = boost::context::make_fcontext(base1, stack_allocator::default_stacksize(), f1);

  std::cout << "main: call start_fcontext(&fcm, fc1, 0)" << std::endl;
  boost::context::jump_fcontext(&fcm, fc1, 0, false);

  std::cout << "main: done" << std::endl;
}