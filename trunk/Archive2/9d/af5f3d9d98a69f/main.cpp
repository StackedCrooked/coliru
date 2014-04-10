#include <memory>
#include <iostream>

struct Base               { virtual void foo() {}; ~Base()        { std::cout << __FUNCTION__ << "\n"; } };
struct Derived1    : Base { virtual void foo() {}; ~Derived1()    { std::cout << __FUNCTION__ << "\n"; } };
struct Derived2    : Base { virtual void foo() {}; ~Derived2()    { std::cout << __FUNCTION__ << "\n"; } };
struct DerivedOops : Base { virtual void foo() {}; ~DerivedOops() { std::cout << __FUNCTION__ << "\n"; } };

struct DynamicDeleter
{
    void operator()(Base* p) const {
        try_delete<Derived1>(p) || try_delete<Derived2>(p) || try_delete<Base>(p)
            ? void(p) 
            : throw std::runtime_error(std::string("Not implemented: ") + typeid(*p).name());
    }

    private: template <typename D> bool try_delete(Base* p) const {
        return (typeid(*p)==typeid(D)) && (delete dynamic_cast<D*>(p), true);
    }
};

template <typename T>
using dynamic = std::unique_ptr<T, DynamicDeleter>;

int main()
{
    dynamic<Base>        b   (new Base);
    dynamic<Derived1>    d1  (new Derived1);
    dynamic<Derived2>    d2  (new Derived2);
    dynamic<DerivedOops> oops(new DerivedOops);

    dynamic<Base> polymorphic;

    polymorphic = std::move(b);
    std::cout << "Deleting a Base through Base*: ok\n"; polymorphic.reset();

    polymorphic = std::move(d1);
    std::cout << "Deleting a Derived1 through Base*: ok\n"; polymorphic.reset();

    polymorphic = std::move(d2);
    std::cout << "Deleting a Derived2 through Base*: ok\n"; polymorphic.reset();

    // deleter not implemented for this
    polymorphic = std::move(oops);
    std::cout << "Deleting a DerivedOops through Base*: NOT ok\n"; polymorphic.reset();
}
