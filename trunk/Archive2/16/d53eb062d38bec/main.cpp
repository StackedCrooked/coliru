struct Base
{
    virtual ~Base() {}
    virtual void f() = 0;
};

struct OtherBase
{
    virtual ~OtherBase() {}
    virtual void g() {}
};

struct Derived: public Base
{
    virtual ~Derived() {}
    virtual void f() {}
};

struct MultiplyDerived: public Base, public OtherBase
{
    virtual ~MultiplyDerived() {}
    virtual void f() {}
    virtual void g() {}
};

struct OtherDerived: public Base
{
    virtual ~OtherDerived() {}
    virtual void f() {}
};

struct DiamondDerived: public Derived, public OtherDerived
{
    virtual ~DiamondDerived() {}
    virtual void f() {}
};

struct VirtuallyDerived: virtual public Base
{
    virtual ~VirtuallyDerived() {}
    virtual void f() {}
};

struct OtherVirtuallyDerived: virtual public Base
{
    virtual ~OtherVirtuallyDerived() {}
    virtual void f() {}
};

struct VirtuallyDiamondDerived: public VirtuallyDerived, public OtherVirtuallyDerived
{
    virtual ~VirtuallyDiamondDerived() {}
    virtual void f() {}
};

struct DoublyVirtuallyDiamondDerived: virtual public VirtuallyDerived, virtual public OtherVirtuallyDerived
{
    virtual ~DoublyVirtuallyDiamondDerived() {}
    virtual void f() {}
};

struct MixedVirtuallyDerived: virtual public Base, public OtherBase
{
    virtual ~MixedVirtuallyDerived() {}
};

struct MixedVirtuallyDiamondDerived: public VirtuallyDerived, public MixedVirtuallyDerived
{
    virtual ~MixedVirtuallyDiamondDerived() {}
    virtual void f() {}
    virtual void g() {}
};

struct VirtuallyMultiplyDerived: virtual public Base, virtual public OtherBase
{
    virtual ~VirtuallyMultiplyDerived() {}
};

struct OtherVirtuallyMultiplyDerived: virtual public Base, virtual public OtherBase
{
    virtual ~OtherVirtuallyMultiplyDerived() {}
};

struct MultiplyVirtuallyDiamondDerived: public VirtuallyMultiplyDerived, public OtherVirtuallyMultiplyDerived
{
    virtual ~MultiplyVirtuallyDiamondDerived() {}
    virtual void f() {}
    virtual void g() {}
};