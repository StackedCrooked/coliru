#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <string>
#include <functional>
#include <type_traits>
#include <queue>

using namespace std;
using namespace chrono;

template <int level, typename F>
void foo(F&& f);

template <typename F>
void foo<10>(F&& f) {
    f();
}

template <int level, typename F>
void foo(F&& f) {
    foo<level+1>(forward<F>(f));
}

template <int level, typename F>
void bar(F f);

template <typename F>
void bar<10>(F f) {
    f();
}

template <int level, typename F>
void bar(F f) {
    bar<level+1>(move(f));
}

template <int level, typename F>
void zoo(F f);

template <typename F>
void zoo<10>(F f) {
    f();
}

template <int level, typename F>
void zoo(F f) {
    zoo<level+1>(f);
}

template <typename C, typename F, typename... Args>
typename C::duration measure(F&& func, Args&&... args) {
    auto start = C::now();
    func(forward<Args>(args)...);
    return C::now() - start;
}

void func() {}

int main() {
    cout << measure<chrono::system_clock>(foo<0, decltype(func)>, func).count() << endl;
    cout << measure<chrono::system_clock>(bar<0, decltype(func)>, func).count() << endl;
    cout << measure<chrono::system_clock>(zoo<0, decltype(func)>, func).count() << endl;
}
