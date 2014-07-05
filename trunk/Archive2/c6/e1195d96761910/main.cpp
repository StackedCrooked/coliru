#include <cstdio>
#include <string>
using std::printf;

template <typename T>
void tellme(T &t) {
  printf("&:  %p\n", (void*)&t);
}
template <typename T>
void tellme(T &&t) {
  printf("&&: %p\n", (void*)&t);
}

int main() {
  tellme(std::string("a"));
  tellme(std::string("a") = std::string("b"));
  tellme(std::move(std::string("a") = std::string("b")));
}
