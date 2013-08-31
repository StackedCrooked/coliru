enum class foo : int {};

int main() {
    char c = 0;
    foo f(static_cast<foo>(c));
    (void)f;
}