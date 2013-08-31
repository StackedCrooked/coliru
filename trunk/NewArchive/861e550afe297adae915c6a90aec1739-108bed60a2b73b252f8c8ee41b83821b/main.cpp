template <typename T>
struct element {
    T value = 0;
};
struct X : element<int>, element<double>, element<float> {};

template <typename T>
T& get(element<T>& e) { return e.value; }

int main() {
    X x;
    get<double>(x);
}