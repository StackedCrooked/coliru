#include <vector>

class B {
};

class A {
    const std::vector<B> m_v;
public:
    A(const std::vector<B>& v) : m_v(v) {}
    void doSomething() {}
};

void foo(void* bar) {
    A* a = (A*)bar;
    a->doSomething();
}

int main() {
    std::vector<B> v;
    std::vector<A > l;
    for (auto i = 0; i < 10; i++) {
        A a(v);
        l.push_back(std::move(a));
        foo((void*)&l[i]);
    }
    return 0;
}
