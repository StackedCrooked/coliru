#include <memory>
#include <cstdint>

// don't language-lawyer me saying that I need to overload more operators 
// related to `operator new`, I'm lazy - and this is just to show that
// the new-initializer won't be called if the allocation fails (ie. returns
// nullptr) on `clang`, whereas `gcc` will do it in either case

void* operator new (std::size_t size, std::nothrow_t const&) noexcept {
  return nullptr;
}

int func () { throw 0; }

int main () {
  return new (std::nothrow) int (func ()) != nullptr;
}