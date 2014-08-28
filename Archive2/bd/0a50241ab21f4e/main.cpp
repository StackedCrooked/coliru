template <int N>
struct X
{
    float ix = 1.f;
    void x(float x) { return -x; }  
};

template <int N>
struct Y : public X<N>
{
#ifdef _MS_VER
    void y(float y) { return x(y * 2) + ix; }
#else
    void y(float y) { return X<N>::x(y * 2) + X<N>::ix; }
#endif
};

int main() {
    Y<2> y;
}
