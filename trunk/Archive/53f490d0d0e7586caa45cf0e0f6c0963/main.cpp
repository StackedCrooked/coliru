#include <memory>
#include <type_traits>

#define CLAW_GEN_CLONE(T) virtual T* clone() const { return new T(*this); } 

namespace claw {
    template<typename T>
    struct default_clone {
        T* operator()(T const& x) const {
            return x.clone();
        }
    };

    template<typename B,
             typename Cloner = default_clone<B>,
             typename Deleter = std::default_delete<B>>
    class poly_val {
    public:
        explicit poly_val(B* x, Cloner cloner_ = Cloner(), Deleter deleter_ = Deleter())
            : obj{x, deleter_}
            , cloner(cloner_) {

        }

        poly_val(poly_val const& other)
            : obj{other.cloner(*other.obj), other.cloner}
            , cloner(other.cloner) {

        }

        poly_val(poly_val&&) = default;

        poly_val& operator=(poly_val other) {
            swap(*this, other);
            return *this;
        }

        poly_val& operator=(poly_val&&) = default;

        ~poly_val() = default;

        void reset(B* x) {
            obj.reset(x);
        }

        void swap(poly_val& other) {
            other.obj.swap(obj);
        }

        template<typename D>
        D& get() {
            return dynamic_cast<D&>(*obj);
        }

        template<typename D = B>
        D const& get() const {
            return dynamic_cast<D&>(*obj);
        }

        B* operator->() {
            return obj.get();
        }

        B const* operator->() const {
            return obj.get();
        }

        B& operator*() {
            return *obj;
        }

        B const& operator*() const {
            return *obj;
        }

        Cloner& get_cloner() {
            return cloner;
        }

        Cloner const& get_cloner() const {
            return cloner;
        }

        Deleter& get_deleter() {
            return obj.get_deleter();
        }

        Deleter const& get_deleter() const {
            return obj.get_deleter();
        }

    private:
        std::unique_ptr<B, Deleter> obj;
        Cloner cloner;

        friend void swap(poly_val& a, poly_val& b) {
            a.swap(b);
        }
    };
}

#include <iostream>

class B {
public:
    CLAW_GEN_CLONE(B);
    virtual ~B() noexcept = default;
    
    virtual void foo() {
        std::cout << "B::foo()\n";
    }
};

class D : public B {
public:
    CLAW_GEN_CLONE(D);
    virtual ~D() noexcept = default;
    
    virtual void foo() override {
        std::cout << "D::foo()\n";
    }
};

class E : public D {
public:
    CLAW_GEN_CLONE(E);
    virtual ~E() noexcept = default;
    
    virtual void foo() override {
        std::cout << "E::foo()\n";
    }
};

int main() {
    claw::poly_val<B> b{new B};
    claw::poly_val<B> d{new D};
    claw::poly_val<B> e{new E};
    
    b->foo();
    d->foo();
    e->foo();
    
    claw::poly_val<B> bc{b};
    claw::poly_val<B> dc{d};
    claw::poly_val<B> ec{e};
    
    bc->foo();
    dc->foo();
    ec->foo();
}
