#include <memory>

template <class T>
struct OwnerPointer {
 private:
  std::shared_ptr<T> impl_;
 public:
 
  // Constructors
  OwnerPointer(T* in) : impl_(in) {}
  OwnerPointer(OwnerPointer<T>&&) = default;  
  OwnerPointer(OwnerPointer<T> const&) = delete;
  
  // Assignment operators
  OwnerPointer& operator=(OwnerPointer<T> const&) = delete;
  OwnerPointer& operator=(OwnerPointer<T>&&) = default;
 
  // Observers
  T* get() const { return impl_.get() }
  T* operator->() const { return impl_.get(); }
  T& operator*() const { return *impl_; }
  
  explicit operator std::weak_ptr<T>() const noexcept {return impl_;}
  explicit operator bool const noexcept { return impl_;}
};