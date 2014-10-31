#include <memory>
#include <new>

template <typename T>
inline void destruct(T& t) { t.~T(); }

template <typename T, typename...Args>
inline void construct(T& t, Args&&...args) {
  ::new((void*)std::addressof(t)) T(std::forward<Args>(args)...);
}

template <typename T>
inline void default_construct(T& t) {
  ::new((void*)std::addressof(t)) T;
}

bool foo() {
  union bar { int i; bool b; };
  union baz { char c; bar b; };
  auto b = baz{'x'};
  destruct(b.c);
  default_construct(b.b);
  construct(b.b.b, true);
  return b.b.b;
}
