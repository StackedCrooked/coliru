#include <boost/shared_ptr.hpp>
#include <iostream>

class Foo { // "abstract"
    public:
        virtual void Destroy () { std::cout << __FUNCTION__ << "\n"; }
    protected:
        virtual ~Foo () {}
};

class FooBase : public Foo {
    public:
        virtual ~FooBase() { std::cout << __FUNCTION__ << "\n"; }

        static void Deleter(FooBase* p) {
            if (p)
                p->Destroy();
            delete p;
        }
};

class FooDerived : public FooBase
{
    ~FooDerived() { std::cout << __FUNCTION__ << "\n"; }
};

int main()
{
    boost::shared_ptr<FooBase> p(new FooDerived, &FooBase::Deleter);
}


