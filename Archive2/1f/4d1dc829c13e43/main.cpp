int main() {
    auto x = [] { };
    class a : decltype(x) { };
    return 0;
}