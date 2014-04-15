template <class Tp>
struct SimpleAllocator {
  typedef Tp value_type;
  SimpleAllocator(/*ctor args*/);
  template <class T> SimpleAllocator(const SimpleAllocator<T>& other);
  Tp* allocate(std::size_t n);
  void deallocate(Tp* p, std::size_t n);
};
template <class T, class U>
bool operator==(const SimpleAllocator<T>&, const SimpleAllocator<U>&);
template <class T, class U>
bool operator!=(const SimpleAllocator<T>&, const SimpleAllocator<U>&);