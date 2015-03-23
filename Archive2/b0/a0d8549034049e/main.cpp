void f(const char*) {}
template<decltype(sizeof(0)) N>
void f(const char (&)[N]) = delete;

int main() {
    f("hello");
}