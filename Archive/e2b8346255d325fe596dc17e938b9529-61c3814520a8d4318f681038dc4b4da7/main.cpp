template<typename T>
struct ID { typedef T type; };

struct S
{
    virtual int m1(int a) const = 0;
    virtual int m2(int a) const = 0;
    virtual int m3(int a) const = 0;
};

struct X : S
{
    virtual int m1(int a) const override { return a; }

#if _MSC_VER
    virtual auto m2(int a) const -> int override { return a; }
#else
    virtual auto m2(int a) const override -> int { return a; }
#endif

#if _MSC_VER
    typedef int m3_t(int) const;
    m3_t m3;
#else
    ID<int (int) const>::type m3;
#endif
};

int X::m3(int a) const { return a; }

int main()
{
    X x;
    return x.m1(1);
}