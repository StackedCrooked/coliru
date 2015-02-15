template <int A, int B, int C> struct StructA
{
    static constexpr int a = A;
    // ...
};

template <int A, int B> struct StructB
{
    static constexpr int a = A;
    // ...
};

template <typename S, typename T> struct StructC
{
    StructC() = default;
    template <typename S1, typename T1> StructC(const StructC<S1, T1>& s) {}
};

void Func(StructC<StructB<4, 5>, double> x)
{
    // do something with x
}

int main()
{
    StructC<StructA<1, 2, 3>, float> a;
    Func(a);
}