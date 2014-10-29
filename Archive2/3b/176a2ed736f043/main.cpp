#include <cstddef>
#include <iostream>

typedef void (*InitializerEntry)();

static void RunInitializers(const void *section, size_t byteCount)
{
  const InitializerEntry begin = reinterpret_cast<const InitializerEntry>(section); 
  begin();
}

void foo() {
  std::cout << "Here";
}

int main() {
  const void *ptr = reinterpret_cast<const void *>(foo);
  RunInitializers(ptr, 0);
}