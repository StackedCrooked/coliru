struct foo {
  static constexpr const void* ptr = reinterpret_cast<const void*>(0x1);
};

auto main() -> int {
  return 0;
}
