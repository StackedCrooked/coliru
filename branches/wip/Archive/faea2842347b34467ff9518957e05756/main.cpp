#include <boost/optional.hpp>
#include <cstddef>
#include <utility>

template<class T>
struct nullable_pointer{
  nullable_pointer() : value(boost::none) {}
    
  nullable_pointer(std::nullptr_t) : value(boost::none) {}
    
  template<class U>
  nullable_pointer(U&& u) : value(std::forward<U>(u)) {}
  
  nullable_pointer& operator=(std::nullptr_t){ value = boost::none; return *this; }
    
  bool operator==(nullable_pointer const& other) const{ return value == other.value; }
  bool operator!=(nullable_pointer const& other) const{ return value != other.value; }
  
  explicit operator bool() const{ return value; }
  
  T& operator*(){ return *value; }
  T const& operator*() const{ return *value; }
  
  T* operator->(){ return &*value; }
  T const* operator->() const{ return &*value; }
    
  boost::optional<T> value;  
};