#include <functional>
struct X {
    void operator()(int i) {}
    void operator()(short s) {}
    void operator()(char c) = delete;
};
int main() {
    std::function<void(int)> i = X();
    std::function<void(short)> s = i;
    std::function<void(char)> c = s;
    c('c');
}