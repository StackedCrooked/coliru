#include <cstddef>

int delete_count;

struct Base {
  virtual ~Base() noexcept = default;
};

struct Singleton
    : public Base {
  void* operator new(size_t sz) noexcept { return instance(); }
  void operator delete(void* ptr) noexcept {
    // the body is supposed to be empty since new() doesn't allocate
    ++delete_count;
  }
  static Singleton* instance() noexcept {
    static Singleton kInstance;
    return &kInstance;
  }
};

#include <cassert>

int main()
{
    Singleton* s = new Singleton;
	Singleton* s2 = new Singleton;
	assert(s == s2);
	assert(s == Singleton::instance());

	delete s;
	assert(1 == delete_count);
	assert(s == Singleton::instance());

	delete s2;  // crashes with free(): invalid pointer
	assert(2 == delete_count);
}
