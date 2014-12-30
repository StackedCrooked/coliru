#include <iostream>
#include <memory>
#include <dlfcn.h>

/* XXX: These casts aren't actually "legal" (N3797 § 5.2.10.8). */
template <typename T>
T* void_to_func(void * const v)
{
  union
  {
    void *vptr;
    T *fptr;
  } cast{ v };
  return cast.fptr;
}

int main()
{
  std::unique_ptr<void, decltype(&dlclose)> handle{ dlopen("libmath.so", RTLD_LAZY), &dlclose };
  auto const fptr(void_to_func<double (double)>(dlsym(handle.get(), "cos")));
  std::cout << fptr(3.14159) << std::endl;
}