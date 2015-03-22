template <typename TObj, template<typename T> class TDerived>
class A;

template <typename TObjL, template<typename T> class TDerivedL, typename TObjR, template<typename T> class TDerivedR>
bool operator==(const A<TObjL, TDerivedL>& l, const A<TObjR, TDerivedR>& r)
{
    return true;
}

template <typename TObj, template<typename T> class TDerived>
class A
{
    template <typename TObjL, template<typename T> class TDerivedL, typename TObjR, template<typename T> class TDerivedR>
    friend bool operator==(const A<TObjL, TDerivedL>& l, const A<TObjR, TDerivedR>& r);
};

template <typename TObj>
class B: public A<TObj, B>
{
};

int main()
{
    B<int> b1, b2;
    b1==b2;
    return 0;
}