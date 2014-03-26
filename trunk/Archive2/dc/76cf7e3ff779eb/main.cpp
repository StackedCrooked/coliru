#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

class Foo { // "abstract"
    public:
        virtual void Destroy () {}
    protected:
        virtual ~Foo () {}
};

class FooBase : public Foo {
    public:
        virtual ~FooBase() { }
};

class FooDerived : public FooBase
{
};

int main()
{
    boost::shared_ptr<FooBase> p(new FooDerived, boost::mem_fn(&Foo::Destroy));
}


