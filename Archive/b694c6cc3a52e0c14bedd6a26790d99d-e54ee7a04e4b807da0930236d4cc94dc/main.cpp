#include <iostream>
#include <utility>
#include <string>

template <class T, typename... Args> void proof_it_works(T&& first) 
{first = 0;}
template <class T, typename... Args> void proof_it_works(T&& first, Args &&...args) {
    first = 0;
    proof_it_works(std::forward<Args>(args)...);
}

template <typename... Args> void f(Args &&...args) {proof_it_works(std::forward<Args>(args)...);}

template<class assigner_type>
struct bitfieldref_type {
    bitfieldref_type(bool value, assigner_type&& assign) :value(value), assign(std::move(assign)) {}
    operator bool() const {return value;}
    bitfieldref_type& operator=(bool v) {assign(v); value=v; return *this;}
private:
    bool value;
    assigner_type assign;
};
template<class assigner_type>
bitfieldref_type<assigner_type> make_bitfieldref(bool value,  assigner_type&& assign) {return {value, std::move(assign)};}
#define bitfieldref(X) make_bitfieldref(X, [&](bool v)->void{X=v;})

int main() {
    struct bits { unsigned int foo:1; };
    bits b{1};
    int a = -1;
    float c = 3.14;
    f(a, bitfieldref(b.foo), c);
    std::cout << a << b.foo << c;
    return 0;
}