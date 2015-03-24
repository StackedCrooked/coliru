//http://stackoverflow.com/questions/29088844/how-to-make-this-template-constexpr-construct-more-elegant-less-verbose
#include <cassert>
#include <type_traits>
#include <cstddef>

template<class T, size_t offset, size_t size, size_t mask=~T(((~0)<<offset<<size)|((1<<offset)-1))>
struct FieldReference {
    explicit FieldReference(T& f) :flags(&f) {}
    operator T() const {return (flags[0]&mask)>>offset;}
    FieldReference& operator=(T v) {
        assert((v&~(mask>>offset))==0);
        flags[0] &= ~mask;
        flags[0] |= (v<<offset);
        return *this;
    }
private:
    T* flags;
};
#define FIELD(Flags,Name,Offset,Size) \
    FieldReference<decltype(Flags),Offset,Size> Name() {return FieldReference<decltype(Flags),Offset,Size>(Flags);} \
    FieldReference<std::add_const<decltype(Flags)>::type,Offset,Size> Name() const {return FieldReference<std::add_const<decltype(Flags)>::type,Offset,Size>(Flags);}

struct Test {
    unsigned long long flags = 0;
    FIELD(flags,one,0,1);
    FIELD(flags,two,1,2);
};

#include <iostream>

int main() {
    Test t;
    t.one() = 1;
    t.two() = 3;
    std::cout << t.two();
    return 0;
}