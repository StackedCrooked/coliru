struct test {
private:
    test() {}
};

int main() {
    #if defined(FIRST_VERSION)
    test x;
    #else
    test* x = new test;
    #endif
    (void)x; // shut up warning
}
    