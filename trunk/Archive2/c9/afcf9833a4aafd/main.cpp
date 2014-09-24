#include <memory>
#include <iostream>

struct Foo {
  Foo() {std::cout << "Hello Foo\n"; }
  ~Foo() { std::cout << "G'bye Foo\n"; }
  void talk() { std::cout << "I'm talkin'\n"; }
};


template <class T>
struct OwnerPointer {
 private:
  std::shared_ptr<T> impl_;
 public:
 
  // Constructors
  OwnerPointer(T* in) : impl_(in) {}
  template<class Deleter>
  OwnerPointer(std::unique_ptr<T, Deleter>&& in) : impl_(std::move(in)) { }
  OwnerPointer(std::shared_ptr<T>&& in) : impl_(std::move(in)) { }
  OwnerPointer(OwnerPointer<T>&&) = default;  
  OwnerPointer(OwnerPointer<T> const&) = delete;

  // Assignment operators
  OwnerPointer& operator=(OwnerPointer<T> const&) = delete;
  OwnerPointer& operator=(OwnerPointer<T>&&) = default;
 
  // Observers
  T* get() const { return impl_.get(); }
  T* operator->() const { return impl_.get(); }
  T& operator*() const { return *impl_; }
  
  explicit operator std::weak_ptr<T>() const noexcept {return impl_;}
  explicit operator bool() const noexcept { return impl_;}
};

template <class T, class... Args>
static OwnerPointer<T> make_owner(Args&&... args) {
  return { std::make_shared<T>(std::forward<Args>(args)...) };
}
  
int main() {
  OwnerPointer<Foo> p = make_owner<Foo>();
}