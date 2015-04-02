void f(int) {}
void f(int, int) {}

template<typename... Ts>
void g(void(*)(Ts...)) {}

int main() {
    g(f);
}