struct Tag;

struct SignalBase {};

struct SignalCopyingBase : public SignalBase
{
    SignalCopyingBase(SignalBase const& s) : SignalBase(s)
    {}
    
    SignalCopyingBase() = default;
};

struct Signal1 : public SignalCopyingBase
{
    using SignalCopyingBase::SignalCopyingBase;
};

struct Signal2 : public SignalCopyingBase
{
    using SignalCopyingBase::SignalCopyingBase;
};


int main()
{ 
    Signal1 s1;
    Signal2 s2(s1);
}