template <class T>
struct optref {
  T* ptr;
  
  constexpr optref() noexcept : ptr(nullptr) {}
  constexpr optref( std::nullopt_t ) noexcept : optref() {};
  constexpr optref( const optref& ) = default; //you can't really move a reference/pointer, plain copying is all we need
  template <class U>
  explicit optref( U& u ) noexcept : ptr(std::addressof(u));
  
  ~optref() = default;
  
  optref& operator=( std::nullopt_t ) noexcept { ptr = nullptr; }
  optref& operator=( optref const& ) = default; //see above
  template <class U>
  optref& operator=( U& u ) { ptr = std::addressof(u); }
  
  constexpr T* operator->() const { return ptr; }
  constexpr T& operator*() const { return *ptr; }
  constexpr explicit operator bool() const { return ptr; }
  constexpr T& value() const { return *ptr; }
  template <class U>
  constexpr T& value_or( U& u ) const { return ptr ? *ptr: u; }
  
  void swap( optref& other ) noexcept { swap(ptr, other.ptr); }
  template <class U>
  void emplace( U& u ) { ptr = std::addressof(u); } 
}