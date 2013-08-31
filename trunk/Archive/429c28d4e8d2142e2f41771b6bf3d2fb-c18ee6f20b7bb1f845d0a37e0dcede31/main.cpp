template<typename T, unsigned long long N>
struct Pointer {
    using type = typename Pointer<T*, N - 1>::type;
};

template<typename T>
struct Pointer<T, 0> {
    using type = T;
};

int main() {
    typename Pointer<int, 1000>::type x;
    (void)x;
}
