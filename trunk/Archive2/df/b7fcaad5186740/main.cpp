template <typename T>
float foo(T t);

template <typename T>
void bar(T t) {
    foo(t);
}

template <typename T>
double foo(T t) {}

int main() {
    bar(42);

}
