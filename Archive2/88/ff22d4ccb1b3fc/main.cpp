void f(int *) {}
void f(int []) {}

int main() {
  f(nullptr);
}
