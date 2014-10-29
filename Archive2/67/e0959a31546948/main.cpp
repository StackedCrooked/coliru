#include <cstddef>
#include <iostream>

typedef void (*InitializerEntry)();

static void RunInitializers(const void *section, size_t byteCount)
{
  InitializerEntry begin = reinterpret_cast<InitializerEntry>(const_cast<void *>(section)); 
  begin();
}

void foo() {
  std::cout << "Here";
}

int main() {
  const void *ptr = reinterpret_cast<const void *>(foo);
  RunInitializers(ptr, 0);
}