template <typename T>
struct foo_traits;

template <typename T>
void bar(T t) {
    foo_traits<T>::foo(t);
}

template <>
struct foo_traits<int> {
    static void foo(int i) {}
};

int main() {
    bar(42);
}
