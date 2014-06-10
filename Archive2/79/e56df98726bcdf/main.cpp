#include <functional>

template<class T>
void foobar (T&& val) { }

int main() {
  std::function<void()> f = [i = std::move(123)]() { foobar(std::move(i)); };
}