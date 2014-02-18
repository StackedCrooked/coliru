struct T {
  explicit T(int) {}
};

int f() { return 0; }

int main() {
  T v3 = {f()}; // works if and only if the type of f() can be implicitly converted to a T
}
