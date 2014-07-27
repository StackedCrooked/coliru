#include <initializer_list>
#include <memory>

using Value = int;

class MaybeUniquePtr {
 public:
  MaybeUniquePtr(bool owned, Value* value) : owned_(owned), value_(value) {}
  MaybeUniquePtr(MaybeUniquePtr&& other) = default;  // Movable
  MaybeUniquePtr(MaybeUniquePtr& other) = delete;    // Not copyable
  MaybeUniquePtr(std::initializer_list<Value*>) = delete;  // No braced init
  ~MaybeUniquePtr() { if (owned_) delete value_; }
 private:
  bool owned_;
  Value* value_;
};

struct MyStruct {
  // MaybeUniquePtr p{nullptr};  // error: call to deleted constructor
  // MaybeUniquePtr p = MaybeUniquePtr{nullptr};  // ditto
  MaybeUniquePtr p = MaybeUniquePtr(true, new int);
};

void Foo() {
  MyStruct ms;
  MyStruct ms2(std::move(ms));
}

int main(void) {
  Foo();
  return 0;
}