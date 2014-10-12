#include <vector>
#include <functional>
#include <iostream>

template<typename T>
class FunctionIterator {
 private:
  std::function<T(size_t)> func_; 
  size_t index_;
 public:
  FunctionIterator(std::function<T(size_t)> func, size_t index) : func_(std::move(func)), index_(index) {}
  
  T                    operator* ()                                 { return func_(index_); }
  FunctionIterator<T>& operator++()                                 { index_++; return *this; }
  T                    operator->()                                 { return operator*(); }
  bool                 operator==(const FunctionIterator<T>& other) { return index_ == other.index_; }
  bool                 operator!=(const FunctionIterator<T>& other) { return index_ != other.index_; }
};

int func(size_t index) {
  // Some function of index
  return index % 3;
}

int main() {
  const size_t size = 10;
  auto begin = FunctionIterator<int>(func, 0);
  auto end = FunctionIterator<int>(func, size);
  std::vector<int> v(begin, end);
  std::cout << "v: ";
  for (auto val : v)
    std::cout << val << " ";
}
