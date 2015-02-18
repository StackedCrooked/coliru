#include <new>
#include <cstdlib>

void* operator new(std::size_t size) {
  constexpr std::size_t alignment_in_bytes = 8;
  void* result;
  bool worked = posix_memalign(&result, alignment_in_bytes, size);

  return worked ? result : nullptr;
}

void* operator new[](std::size_t size) {
  constexpr std::size_t alignment_in_bytes = 8;
  void* result;
  bool worked = posix_memalign(&result, alignment_in_bytes, size);

  return worked ? result : nullptr;
}

void operator delete(void* ptr) noexcept { std::free(ptr); }

int main() {
return 0;
}