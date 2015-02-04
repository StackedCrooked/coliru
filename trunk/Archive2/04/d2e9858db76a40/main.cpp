template<typename T, unsigned long N>
struct array {
  T data[N];
};

auto copy(array<int, 32> const& x) {
  return x;
}