#include <cassert>

struct B { };             // not polymorphic
struct D1 : public B {};  // not polymorphic
struct D2 : private B {}; // not polymorphic

D1 d1;
D2 d2;



template <typename To, typename From>
const To* my_dynamic_cast(const From* obj) {
    try {
        throw obj;
    }
    catch (const To* pb) {
        return pb;
    }
    catch (...) {
    }
    return nullptr;
}

int main() {
    assert(my_dynamic_cast<B>(&d1)); // from derived* to base* same as static_cast<B*>(&d1)
    
    B* b1=&d1; // here I hide the type 
    assert(my_dynamic_cast<D1>(b1)); // from base* to derived* same as dynamic_cast<D*>(b1) (with virtual functions in B)
        
    assert(!(my_dynamic_cast<B>(&d2))); // Notice the negation.
}