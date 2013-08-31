struct T {
    int m_x;
    T(int x) : m_x(x) {}

    T(T const volatile& v) = default;
};

int main() {
    volatile T v(2);
    T nv(1);
    nv = v; // nv.m_x = 0
}
