#include <cassert>

class inheritance_checker {

    typedef void (*thrower_t)();
    typedef bool (*catcher_t)(thrower_t);

public:

    template <typename T>
    static inheritance_checker create() {
        return inheritance_checker(concrete_thrower<T>, concrete_catcher<T>);
    } 

    bool is_derived_from(const inheritance_checker& other) const {
        return other.catcher_(thrower_);
    }

    bool is_base_of(const inheritance_checker& other) const {
        return catcher_(other.thrower_);
    }

private:

    template <typename T>
    static void concrete_thrower() {
        throw static_cast<T*>(nullptr);
    }

    template <typename T>
    static bool concrete_catcher(thrower_t thrower) {
        try         { thrower();   }
        catch (T*)  { return true; }
        catch (...) {              }
        return false;
    }

    inheritance_checker(thrower_t thrower, catcher_t catcher) :
        thrower_(thrower), catcher_(catcher) {
    }

    thrower_t thrower_;
    catcher_t catcher_;
};

class A {};
class B : public A {};
class C : public B {};
class D {};

int main() {

    auto a = inheritance_checker::create<A>();
    auto b = inheritance_checker::create<B>();
    auto c = inheritance_checker::create<C>();
    auto d = inheritance_checker::create<D>();

    assert( a.is_base_of(a));
    assert( a.is_base_of(b));
    assert( a.is_base_of(c));
    assert(!a.is_base_of(d));

    assert( a.is_derived_from(a));
    assert(!a.is_derived_from(b));
    assert(!a.is_derived_from(c));
    assert(!a.is_derived_from(d));

    assert(!b.is_base_of(a));
    assert( b.is_base_of(b));
    assert( b.is_base_of(c));
    assert(!b.is_base_of(d));

    assert( b.is_derived_from(a));
    assert( b.is_derived_from(b));
    assert(!b.is_derived_from(c));
    assert(!b.is_derived_from(d));

    assert(!c.is_base_of(a));
    assert(!c.is_base_of(b));
    assert( c.is_base_of(c));
    assert(!c.is_base_of(d));

    assert( c.is_derived_from(a));
    assert( c.is_derived_from(b));
    assert( c.is_derived_from(c));
    assert(!c.is_derived_from(d));

    assert(!d.is_base_of(a));
    assert(!d.is_base_of(b));
    assert(!d.is_base_of(c));
    assert( d.is_base_of(d));

    assert(!d.is_derived_from(a));
    assert(!d.is_derived_from(b));
    assert(!d.is_derived_from(c));
    assert( d.is_derived_from(d));
}