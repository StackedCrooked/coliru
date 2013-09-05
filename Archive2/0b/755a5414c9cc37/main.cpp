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
struct FinalUserDefinedType {
    template<typename C, typename AWithDefault = A>
    struct CurryType {
        typedef Outer<AWithDefault, B, C> type;
    };

    typename CurryType<int>::type AnIntOuter;
    typename CurryType<float>::type AFloatOuter;
    // Note the compiler error here:
    /*typename*/ CurryType<double, int>::type AnOverriddenDefault;
};
 
int main()
{
    FinalUserDefinedType<bool, double> a;
    (void)a; // suppress "unused variable" warning
}
