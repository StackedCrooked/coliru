template <typename T> struct element {};
struct X : element<int>, element<double>, element<float> {};

template <typename T>
T& get(element<T>&) { throw 17; }

int main() {
    X x;
    get<double>(x);
}