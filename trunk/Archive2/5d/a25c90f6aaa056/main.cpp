template <typename T>
void bar(T t) {
    foo(t);

}

template <typename T>
void foo(T t) {}

int main() {
    bar(42);

}
