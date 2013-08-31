template <int I, typename T>
struct element {
    T value = 0;
};
struct X : element<0, int>, element<1, double>, element<2, float> {};

template <typename T, int I>
T& get(element<I, T>& e) { return e.value; }

template <int I, typename T>
T& get(element<I, T>& e) { return e.value; }

int main() {
    X x;
    get<double>(x);
    get<2>(x);
}