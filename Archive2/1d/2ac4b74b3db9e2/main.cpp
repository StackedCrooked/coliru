template<typename T>
struct Outer {
    template<typename U>
    struct Inner {
        int x;
    };
    template<>
    struct Inner<int> {
        double f;
    };
};

int main() {
}