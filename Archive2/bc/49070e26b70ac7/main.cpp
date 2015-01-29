template<typename>
struct type {
  template<typename Up>
  constexpr void operator()(Up&&) const noexcept {
  }
};

template<typename Tp>
struct wrapper {
  using type_ = type<Tp>;
  static constexpr type_ object{};
};

int main() {
  wrapper<void>::object(1);
  return 0;
}