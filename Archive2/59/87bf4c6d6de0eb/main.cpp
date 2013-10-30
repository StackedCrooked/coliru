#include <iostream>

using std::clog;

template <class TBase> struct Templated : public TBase
{
    virtual void Test(void)
    {
        static_cast<TBase*>(this)->BaseTest();
        // BaseTest ();
    }
};

struct OneBase
{
    virtual void BaseTest(void) = 0;
};

struct TwoBase : public OneBase
{
    virtual void BaseTest(void) override { }
};

struct ThreeBase : public TwoBase
{
    virtual void BaseTest(void) override { clog << "TreeBase\n"; }
};

int main ()
{
    Templated<ThreeBase> instance;
	instance.Test();
}
