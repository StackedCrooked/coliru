#include <memory>

template<typename T>
using uptr = std::unique_ptr<T>;

struct Obj {
  Obj (uptr<int> up1, uptr<int> up2) {
    /* ... */
  }
};

int
main (int argc, char *argv[])
{
  Obj potential_leak (uptr<int> (new int), uptr<int> (new int));
  Obj actually_safe  {uptr<int> (new int), uptr<int> (new int)};
}