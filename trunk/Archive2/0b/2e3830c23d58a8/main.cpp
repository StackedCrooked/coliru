template <int N>
struct X
{
    float ix = 1.f;
    void x(float x) { return -x; }  
};

template <int N>
struct Y : public X<N>
{
    using X<N>::ix;
    using X<N>::x;
    void y(float y) { return x(y * 2) + ix; }
};

int main() {
    Y<2> y;
}
