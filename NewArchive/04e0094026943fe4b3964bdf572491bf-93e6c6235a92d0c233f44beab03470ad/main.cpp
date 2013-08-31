enum A { A_1, A_2, A_3, A_4 };
enum B { B_1, B_2, B_3, B_4 };

#include <cassert> // for assert
#include <utility> // for std::swap

struct AorB
{
    enum Discriminant { isNil, isA, isB } discriminant;

    union
    {
        A valA;
        B valB;
    };

    AorB() : discriminant(isNil) {}

    A asA() const { assert(discriminant==isA); return valA; }
    B asB() const { assert(discriminant==isB); return valB; }

    explicit operator A() const { return asA(); }
    explicit operator B() const { return asB(); }

    AorB(A valA) : discriminant(isA), valA(valA) {}
    AorB(B valB) : discriminant(isB), valB(valB) {}

    friend void swap(AorB& a, AorB& b) {
        auto tmp = a; 
        a.discriminant = b.discriminant;
        a.safe_set(b.safe_get());

        b.discriminant = tmp.discriminant;
        b.safe_set(tmp.safe_get());
    }

    AorB& operator=(AorB implicit_conversion) {
        swap(implicit_conversion, *this);
        return *this;
    }

    bool operator==(AorB other) const {
        return 
            discriminant == other.discriminant && 
            safe_get()   == other.safe_get();
    }

  private:
    void safe_set(int val) {
        switch(discriminant) {
            case isA: valA = static_cast<A>(val); break;
            case isB: valB = static_cast<B>(val); break;
            case isNil: break;
        }
    }
    int safe_get() const {
        switch(discriminant) {
            case isA: return valA;
            case isB: return valB;
            case isNil: 
            default:  return 0;
        }
    }
};

#include <iostream>

int main()
{
    A a = A_3;
    B b = B_1;

    AorB any;

    // any is isNil now
    any = b; // makes it isB
    any = a; // makes it isA

    if (any == A_2) // comparison is fine, because any is in `isA` now
    {
        std::cout << "Whoops, should be A_3, really\n"; // doesn't happen
    }

    if (any == B_2) // comparison
    {
        std::cout << "Whoops, should not match"; // doesn't happen
    }

    a = static_cast<A>(any); // valid cast
    b = static_cast<B>(any); // fails assertion
}
