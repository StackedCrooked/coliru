template <typename T, T Expected, typename U, U Actual>
void check_eq() {
  static_assert(Expected == Actual, "Equality check failed!");
}

#define COMPILE_CHECK_EQ(a, b) \
  check_eq<decltype(a), a, decltype(b), b>()

int main() {
  COMPILE_CHECK_EQ(sizeof(void*), 8);
  COMPILE_CHECK_EQ(sizeof(int), 6);
}
