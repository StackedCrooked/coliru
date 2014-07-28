typedef struct internal_data * Opaque;

struct internal_data { int a; };

template<typename T>
struct Internal {
 T data;
};

template <typename T>
Opaque map_internal(Internal<T>* p)
{
  return reinterpret_cast<Opaque>(p);
}

template <typename T>
Internal<T>* remap_internal(Opaque p)
{
  return reinterpret_cast<Internal<T>*>(p);
}

template<typename T>
Opaque Initialise(T data) {
  Internal<T>* t = new Internal<T>();
  t->data = data;
  return map_internal(t);
}

#include <cassert>

int main(int argc, char** argv)
{
  Opaque o = Initialise(argc);
  (void)o;

  Internal<int>* pt = new Internal<int>();
  Opaque o2 = map_internal(pt);
  Internal<int>* p = remap_internal<int>(o2);
  assert(p == pt);
  return 0;
}