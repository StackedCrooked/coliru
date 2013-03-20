namespace aux
{
    template<typename T> struct remove_member_pointer;

    template<typename T, typename C>
    struct remove_member_pointer<T C::*> { typedef T type; };

#if _MSC_VER // using a workaround for const methods:
    template<typename R, typename C, typename... A>
    struct remove_member_pointer<R (C::*)(A...)const> { typedef R type(A...) const; };

    template<typename R, typename C, typename... A>
    struct remove_member_pointer<R (__stdcall C::*)(A...)const> { typedef R __stdcall type(A...) const; };

    // TODO: add other calling conventions
#endif
}

struct S
{
    virtual int m0(int a) const = 0;
    virtual int m1(int a) const = 0;
    virtual int m2(int a) const = 0;
    virtual int m3(int a) const = 0;
};

struct X : S
{
    int m0(int a) const { return a; }    
    virtual int m1(int a) const override { return a; }

#if _MSC_VER
    virtual auto m2(int a) const -> int override { return a; }
#else
    virtual auto m2(int a) const override -> int { return a; }
#endif

    aux::remove_member_pointer<decltype(&S::m3)>::type m3;
};

int X::m3(int a) const { return a; }

int main()
{
    X x;
    return x.m1(1);
}