template<typename T, typename... Rest>
struct foo {};

template<class... Ts>
void bar(foo<Ts...>) {}

int main() {
    foo<int, bool> f;
    bar(f);
}