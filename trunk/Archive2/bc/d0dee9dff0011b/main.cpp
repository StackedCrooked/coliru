#include <functional>
using std::function;
void f(const function<void()> &) { }
int main() {
    f([] { return 0; });
}