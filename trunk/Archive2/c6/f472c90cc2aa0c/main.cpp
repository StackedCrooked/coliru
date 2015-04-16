class EnumA
{
    int value_;
public:
    explicit EnumA(int v)
        : value_{v}
    {}
    int value() const
    {
        return value_;
    }
};
struct EnumB: EnumA
{
    enum EnumB_T{one,two};
    explicit EnumB(EnumB_T v)
        : EnumA{v}
    {}
    EnumB_T value() const
    {
        return EnumB_T(EnumA::value());
    }
};

struct A
{
    virtual const EnumA &func() const
    {
        static thread_local EnumA result{0};
        return result = EnumA{1};
    }
};

struct B: A
{
    virtual const EnumB &func() const override
    {
        static thread_local EnumB result{EnumB::one};
        return result = EnumB{EnumB::two};
    }
};

int main()
{
    
}