#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <type_traits>

#ifndef _MSC_VER
#   include <cxxabi.h>
#endif

namespace {
template <typename T>
std::string type_name() {
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
           (
#ifndef _MSC_VER
                abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                           nullptr, nullptr),
#else
                nullptr,
#endif
                std::free
           );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

struct A {
    ~A() { std::cout << "Deleting A\n"; }
};


struct B : public A
{
    ~B() { std::cout << "Deleting B\n"; }
};

// Convert given pointer type to T and delete.
template <typename T>
struct deleter {
    template <typename U>
    void operator () (U* ptr) const {
        if (ptr) {
            T* t_ptr = static_cast<T*>(ptr);
            std::cout << "Destroy " << type_name<T>() << " at " << t_ptr << '\n';
            delete t_ptr;
        }
    }
};

// Create a unique_ptr with statically encoded deleter type.
template <typename T, typename...Args>
inline std::unique_ptr<T, deleter<T>>
make_unique_with_deleter(Args&&...args) {
    auto ptr = new T(std::forward<Args>(args)...);
    std::cout << "Allocate " << type_name<T>() << " at " << ptr << '\n';
    return std::unique_ptr<T, deleter<T>>{ptr};
}

// Convert a unique_ptr with statically encoded deleter to
// a pointer to different type while maintaining the
// statically encoded deleter.
template <typename T, typename U, typename W>
inline std::unique_ptr<T, deleter<W>>
unique_with_deleter_cast(std::unique_ptr<U, deleter<W>> ptr) {
    T* t_ptr{ptr.release()};
    return std::unique_ptr<T, deleter<W>>{t_ptr};
}

// Create a unique_ptr to T with statically encoded
// deleter for type U.
template <typename T, typename U, typename...Args>
inline std::unique_ptr<T, deleter<U>>
make_unique_with_deleter(Args&&...args) {
    return unique_with_deleter_cast<T>(
        make_unique_with_deleter<U>(std::forward<Args>(args)...)
    );
}
} // anonymous namespace

int main() {
    auto ptr = make_unique_with_deleter<A, B>();
    // std::unique_ptr<A> bob = std::move(ptr); // Correctly fails to compile.
}
