template<const char* s>
int f() { return 0; }

int main() {
    f<"hello">(); // error
    const char* hello = "hello";
    f<hello>(); // error
}