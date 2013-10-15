int main() {
    const char hello[] = "Hello World";
    static_assert(sizeof(hello) == 12, "should work");
    static_assert(hello[0] == 'H', "doesn't");
}