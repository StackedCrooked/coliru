#include <map>

typedef std::map<int, int, bool(*)(int, int)> Objs;

int main() {

#if 0
  // Compiles and links as expected.
  Objs objs{[](int a, int b) {
    return a < b;
  }};
#endif

#if 1
  // FIXME The lambda definition for the key-comparing function is
  // missing; why does this compile and link?
  Objs objs;
#endif

  objs.emplace(99997, 4210124);
  (void)objs;
  return 0;
}