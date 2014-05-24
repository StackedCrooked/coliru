template<typename F>
auto fix(F f) {
    return f(f);
}

int main() {
    fix([] (auto f) { f(f); });
    return 0;
}
