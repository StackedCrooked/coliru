#include <memory>
#include <iostream>

struct Foo {
  Foo() {std::cout << "Hello Foo\n"; }
  ~Foo() { std::cout << "G'bye Foo\n"; }
  void talk() { std::cout << "I'm talkin'\n"; }
};

template <class T>
class ObserverPointer;  // Forward declaration.

template<class T>
class OwnerPointer;  // Forward declaration.

// RAII object that can be obtained from ObserverPointer
// that ensures the ObserverPointer does not expire.
// Only operation is to test validity.
template <class T>
class ObserverLock {
 friend ObserverPointer<T>;
 private:
  std::shared_ptr<T> impl_;
  ObserverLock(const std::weak_ptr<T>& in) : impl_(in.lock()) {}
 public:
  // Movable.
  ObserverLock(ObserverLock&&) = default;
  ObserverLock& operator=(ObserverLock&&) = default;
  
  // Not copyable.
  ObserverLock& operator=(const ObserverLock&) = delete;
  ObserverLock(const ObserverLock&) = delete;
  
  // Test validity.
  explicit operator bool() const noexcept { return impl_ != nullptr;} 
};

template <class T>
class ObserverPointer {
 private:
  std::weak_ptr<T> impl_;
  T*               raw_;
 public:
  ObserverPointer(const OwnerPointer<T>& own) noexcept : impl_(own.impl_), raw_(own.get()) {}
  
  T* get() const { return raw_; }
  T* operator->() const { return raw_; }
  T& operator*() const { return *raw_; }
  
  ObserverPointer() : impl_(), raw_(nullptr) { }
  ObserverPointer(const ObserverPointer& in) = default;
  ObserverPointer(ObserverPointer&& in) = default;
  ObserverPointer& operator=(const ObserverPointer& in) = default;
  ObserverPointer& operator=(ObserverPointer&& in) = default; 
  
  bool expired() { return impl_.expired(); }  
  ObserverLock<T> lock() { return ObserverLock<T>(impl_); }
};

template <class T>
struct OwnerPointer {    
 friend ObserverPointer<T>;    
 private:
  std::shared_ptr<T> impl_;
 public:
 
  // Constructors
  explicit OwnerPointer(T* in) : impl_(in) {}
  template<class Deleter>
  OwnerPointer(std::unique_ptr<T, Deleter>&& in) : impl_(std::move(in)) { }
  OwnerPointer(std::shared_ptr<T>&& in) noexcept : impl_(std::move(in)) { }
  OwnerPointer(OwnerPointer<T>&&) noexcept = default;  
  OwnerPointer(OwnerPointer<T> const&) = delete;

  // Assignment operators
  OwnerPointer& operator=(OwnerPointer<T> const&) = delete;
  OwnerPointer& operator=(OwnerPointer<T>&&) = default;
 
  T* get() const { return impl_.get(); }
  T* operator->() const { return impl_.get(); }
  T& operator*() const { return *impl_; }
  
  explicit operator ObserverPointer<T>() const noexcept { return ObserverPointer<T>(impl_);}
  explicit operator bool() const noexcept { return impl_;}
};
  
// Convenience function equivalent to make_shared
template <class T, class... Args>
OwnerPointer<T> make_owner(Args && ...args) {
  return OwnerPointer<T>(new T(std::forward<Args>(args)...));
}
  
int main() {
  auto owner = make_owner<Foo>();
  ObserverPointer<Foo> observer = owner; 
  auto lock = observer.lock();
  if (lock)
   observer->talk();
}