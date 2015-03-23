template<typename = void>
void f(const char*) {}
template<typename CharT, decltype(sizeof(0)) N>
void f(CharT (&)[N]) = delete;

int main() {
    f("lol");
}