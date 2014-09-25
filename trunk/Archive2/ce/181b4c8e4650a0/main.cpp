int main() {
  auto lambda1 = []() mutable {};
  decltype(lambda1) lambda2;
  (void) lambda2;
}