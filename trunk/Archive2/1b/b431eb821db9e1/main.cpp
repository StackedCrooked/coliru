#include <iostream>
#include <memory>

struct Base
{
    virtual ~Base() = default;

    struct Inner
    {
        Inner(Base &b)
        : inst(b)
        {
        }
        virtual ~Inner() = default;

        virtual void f() = 0;

        virtual Base &instance()
        {
            return inst;
        }

        struct Factory
        {
            virtual ~Factory() = default;
    
            virtual std::unique_ptr<Inner> produce() = 0;
        };

    private:
        Base &inst;
    };

    virtual Inner::Factory &inner_factory() = 0;
};

struct Derived
: virtual Base
{
    Derived(int x)
    : v{x}
    {
    }

    struct Inner
    : virtual Base::Inner
    {
        Inner(Derived &d)
        : Base::Inner{d}
        , inst(d)
        {
        }

        virtual void f()
        {
            std::cout << inst.v << std::endl;
        }
        virtual void g(int x)
        {
            inst.v = x;
        }

        virtual Derived &instance() //fine
        {
            return inst;
        }

        struct Factory
        : virtual Base::Inner::Factory
        {
            Factory(Derived &d)
            : inst(d)
            {
            }

            virtual std::unique_ptr<Inner> produce() override //problem
            {
                return std::unique_ptr<Inner>{new Inner{inst}};
            }

        private:
            Derived &inst;
        };

    private:
        Derived &inst;
    };

    virtual Inner::Factory &inner_factory() //fine
    {
        return f;
    }

private:
    Inner::Factory f {*this};
    int v;
};

int main()
{
    Derived d {6};
    auto inner = d.inner_factory().produce();
    inner->f();
    inner->g(7);
    inner->f();
}