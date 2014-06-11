#include <iostream>
#include <cstddef>
#include <cassert>

struct property_tag {};

template<class V, class T, V(T::*G)() const>
struct r_property {
    T const& self() const { return *(T*)((char*)(this) - ((char*)&(((T*)this)->properties) - (char*)this)); }
    operator V() const { return (this->self().*G)(); }
};

template<class V, class T, void(T::*S)(V)>
struct w_property {
    T& self() { return *(T*)((char*)(this) - ((char*)&(((T*)this)->properties) - (char*)this)); }
    w_property& operator=(V v) { (this->self().*S)(v); return *this; }
};

template<class V, class T, V(T::*G)() const, void(T::*S)(V)>
struct rw_property: r_property<V, T, G>, w_property<V, T, S> {
    using w_property<V, T, S>::operator=;
};

class TS {
private:
    float celsius_;
    
    float get_celsius() const { return celsius_; }
    void set_celsius(float v) { celsius_ = v; }
    float get_kelvin() const { return celsius_ + 273.15f; }
    void set_kelvin(float k) { celsius_ = k - 273.15f; }

public:
    union {
        property_tag properties;
        rw_property<float, TS, &TS::get_celsius, &TS::set_celsius> celsius;
        rw_property<float, TS, &TS::get_kelvin, &TS::set_kelvin> kelvin;
    };
};

int main() {
    TS s;
    s.kelvin = 0;
    float f = s.celsius;

    std::cout << f << std::endl;
    std::cout << sizeof(s) << std::endl;
}