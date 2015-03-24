//http://stackoverflow.com/questions/29088844/how-to-make-this-template-constexpr-construct-more-elegant-less-verbose
#include <cassert>
#include <type_traits>
#include <cstddef>

template<class T, size_t offset_, size_t size_>
struct FieldReference {
    static const size_t offset = offset_;
    static const size_t size = size_;
    static const size_t mask = ~T(((~0)<<offset<<size)|((1<<offset)-1));
    
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
#define FIRSTFIELD(Flags,Name,Size) \
    auto Name() -> FieldReference<decltype(Flags),0,Size> {return FieldReference<decltype(Flags),0,Size>(Flags);} \
    FieldReference<std::add_const<decltype(Flags)>::type,0,Size> Name() const {return FieldReference<std::add_const<decltype(Flags)>::type,0,Size>(Flags);}
#define FIELD(Flags,Name,Previous,Size) \
    auto Name() -> FieldReference<decltype(Flags),decltype(Previous())::offset,Size> {return FieldReference<decltype(Flags),decltype(Previous())::offset,Size>(Flags);} \
    auto Name() const -> FieldReference<std::add_const<decltype(Flags)>::type,decltype(this->Previous())::offset,Size> {return FieldReference<std::add_const<decltype(Flags)>::type,decltype(Previous())::offset,Size>(Flags);}

struct Test {
    unsigned long long flags = 0;
    FIRSTFIELD(flags,one,1);
    FIELD(flags,two,one,2);
};

#include <iostream>

int main() {
    Test t;
    t.one() = 1;
    t.two() = 3;
    std::cout << t.two();
    return 0;
}