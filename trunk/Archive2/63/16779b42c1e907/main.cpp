#include <iostream>
#include <type_traits>

struct better_type_info {
    virtual void check() const = 0;
    virtual bool IsDerivedFrom(const better_type_info& other) const = 0;
};
template<typename T> struct better_type_info_impl : better_type_info {
    better_type_info_impl() {}
    void check() const override final {
        throw (T*)nullptr;
    }
    bool IsDerivedFrom(const better_type_info& other) const override final {        
        try {
            other.check();
        } catch(T* p) {
            return true;
        } catch(...) {
            return false;
        }
    }
};
template<typename T>  const better_type_info& better_typeinfo() {
    static const better_type_info_impl<T> info;
    return info;
}
struct Base { virtual ~Base() {} };
struct Derived : Base {};

int main() {
    std::cout << std::boolalpha << better_typeinfo<Base>().IsDerivedFrom(better_typeinfo<Derived>());
}