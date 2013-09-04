struct b {};
struct c {};

template <typename A, typename B = b, typename C = c>
struct Outer
{
    typedef A typeA;
    typedef B typeB;
    typedef C typeC;
};

template<typename A, typename B>
struct AnotherUserDefinedType {
    template<typename CC, typename AA = A, typename BB = B>
    struct Inner : public Outer<AA, BB, CC> {};

    Inner<int> AnIntInner;
    Inner<float> AFloatInner;

};

int main()
{
    AnotherUserDefinedType<bool, double> a;
}
