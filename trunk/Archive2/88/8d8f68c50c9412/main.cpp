template<typename T, typename U>
struct OuterInner<T, U> {};

template<typename T>
struct Outer {
    template<typename U>
    using Inner = OuterInner<T, U>;
};

template<typename T>
struct OuterInner<T, int> {};

int main() {
}