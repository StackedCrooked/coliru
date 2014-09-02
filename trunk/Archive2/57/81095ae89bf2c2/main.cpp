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

    private:
        Base &inst;
    };

    std::unique_ptr<Inner> new_inner()
    {
        return std::unique_ptr<Inner>{produce_new_inner()};
    }

private:
    virtual Inner *produce_new_inner() = 0;
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
        virtual void g(int x) //just a random example
        {
            inst.v = x;
        }

        virtual Derived &instance() //fine
        {
            return inst;
        }

    private:
        Derived &inst;
    };

    std::unique_ptr<Inner> new_inner()
    {
        return std::unique_ptr<Inner>{produce_new_inner()};
    }

private:
    virtual Inner *produce_new_inner() override
    {
        return new Inner{*this};
    }

private:
    int v;
};

int main()
{
    Derived d {6};
    auto inner = d.new_inner();
    inner->f();
    inner->g(7);
    inner->f();
}