template <typename T>
auto g(T t) { return t; }

template <typename T>
T g(T t) { return t; }

int main() {
  (void)g(1);
}