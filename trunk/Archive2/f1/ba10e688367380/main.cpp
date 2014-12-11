template <typename... Args>
inline bool NotNull(Args... args) {
  return true && (args... != nullptr);
}
int main() {
  NotNull(true, false, false);
}
