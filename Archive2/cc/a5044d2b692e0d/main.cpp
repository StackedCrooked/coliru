template<typename T>
struct test {
    template<typename V>
    friend void g(V v);
};

template<typename V = int>
void g(V v = {}) {}

int main() {
    int stuff = 10;
    g();
    g(stuff);
}