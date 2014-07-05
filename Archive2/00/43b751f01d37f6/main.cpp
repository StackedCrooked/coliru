#include <cstdio>
using std::printf;

class tester {
public:
  tester(const char *v) {
    printf("tester(const char *v) %p - %s\n", (void*)this, v);
  }
};

void tellme(const tester &t) {
  printf("const tester &: %p\n", (void*)&t);
}
void tellme(tester &&t) {
  printf("tester &&: %p\n", (void*)&t);
}

int main() {
  tellme(tester("a") = tester("b"));
}
