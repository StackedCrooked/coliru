#include <iostream>
#include <string>

template<class T>
class intWrapperImpl {
    T value;
public:
    typedef T value_type;
    intWrapperImpl() :value() {}
    intWrapperImpl(T v) :value(v) {}
    operator T() const {return value;}
    //modifiers
    intWrapperImpl& operator=(T v) {value=v; return *this;}
    intWrapperImpl& operator+=(T v) {value+=v; return *this;}
    intWrapperImpl& operator-=(T v) {value-=v; return *this;}
    intWrapperImpl& operator*=(T v) {value*=value; return *this;}
    intWrapperImpl& operator/=(T v) {value/=value; return *this;}
    intWrapperImpl& operator%=(T v) {value%=value; return *this;}
    intWrapperImpl& operator++() {++value; return *this;}
    intWrapperImpl& operator--() {--value; return *this;}
    intWrapperImpl operator++(int) {return intWrapperImpl(value++);}
    intWrapperImpl operator--(int) {return intWrapperImpl(value--);}
    intWrapperImpl& operator&=(T v) {value&=v; return *this;}
    intWrapperImpl& operator|=(T v) {value|=v; return *this;}
    intWrapperImpl& operator^=(T v) {value^=v; return *this;}
    intWrapperImpl& operator<<=(T v) {value<<=v; return *this;}
    intWrapperImpl& operator>>=(T v) {value>>=v; return *this;}
    //accessors
    intWrapperImpl operator+() const {return intWrapperImpl(+value);}
    intWrapperImpl operator-() const {return intWrapperImpl(-value);}
    intWrapperImpl operator!() const {return intWrapperImpl(!value);}
    intWrapperImpl operator~() const {return intWrapperImpl(~value);}
    //friends
    friend intWrapperImpl operator+(intWrapperImpl iw, intWrapperImpl v) {return iw+=v;}
    friend intWrapperImpl operator+(intWrapperImpl iw, T v) {return iw+=v;}
    friend intWrapperImpl operator+(T v, intWrapperImpl iw) {return intWrapperImpl(v)+=iw;}
    friend intWrapperImpl operator-(intWrapperImpl iw, intWrapperImpl v) {return iw-=v;}
    friend intWrapperImpl operator-(intWrapperImpl iw, T v) {return iw-=v;}
    friend intWrapperImpl operator-(T v, intWrapperImpl iw) {return intWrapperImpl(v)-=iw;}
    friend intWrapperImpl operator*(intWrapperImpl iw, intWrapperImpl v) {return iw*=v;}
    friend intWrapperImpl operator*(intWrapperImpl iw, T v) {return iw*=v;}
    friend intWrapperImpl operator*(T v, intWrapperImpl iw) {return intWrapperImpl(v)*=iw;}
    friend intWrapperImpl operator/(intWrapperImpl iw, intWrapperImpl v) {return iw/=v;}
    friend intWrapperImpl operator/(intWrapperImpl iw, T v) {return iw/=v;}
    friend intWrapperImpl operator/(T v, intWrapperImpl iw) {return intWrapperImpl(v)/=iw;}
    friend intWrapperImpl operator%(intWrapperImpl iw, intWrapperImpl v) {return iw%=v;}
    friend intWrapperImpl operator%(intWrapperImpl iw, T v) {return iw%=v;}
    friend intWrapperImpl operator%(T v, intWrapperImpl iw) {return intWrapperImpl(v)%=iw;}
    friend intWrapperImpl operator&(intWrapperImpl iw, intWrapperImpl v) {return iw&=v;}
    friend intWrapperImpl operator&(intWrapperImpl iw, T v) {return iw&=v;}
    friend intWrapperImpl operator&(T v, intWrapperImpl iw) {return intWrapperImpl(v)&=iw;}
    friend intWrapperImpl operator|(intWrapperImpl iw, intWrapperImpl v) {return iw|=v;}
    friend intWrapperImpl operator|(intWrapperImpl iw, T v) {return iw|=v;}
    friend intWrapperImpl operator|(T v, intWrapperImpl iw) {return intWrapperImpl(v)|=iw;}
    friend intWrapperImpl operator^(intWrapperImpl iw, intWrapperImpl v) {return iw^=v;}
    friend intWrapperImpl operator^(intWrapperImpl iw, T v) {return iw^=v;}
    friend intWrapperImpl operator^(T v, intWrapperImpl iw) {return intWrapperImpl(v)^=iw;}
    friend intWrapperImpl operator<<(intWrapperImpl iw, intWrapperImpl v) {return iw<<=v;}
    friend intWrapperImpl operator<<(intWrapperImpl iw, T v) {return iw<<=v;}
    friend intWrapperImpl operator<<(T v, intWrapperImpl iw) {return intWrapperImpl(v)<<=iw;}
    friend intWrapperImpl operator>>(intWrapperImpl iw, intWrapperImpl v) {return iw>>=v;}
    friend intWrapperImpl operator>>(intWrapperImpl iw, T v) {return iw>>=v;}
    friend intWrapperImpl operator>>(T v, intWrapperImpl iw) {return intWrapperImpl(v)>>=iw;}
};
typedef intWrapperImpl<int> intWrapper;
typedef intWrapperImpl<unsigned> uintWrapper;
typedef intWrapperImpl<short> shortWrapper;
typedef intWrapperImpl<char> charWrapper;
typedef intWrapperImpl<unsigned long long> ullWrapper;

#include <iostream>

int main() {
    intWrapper a = 42;
    intWrapper b = 999999999;
    a += b;
    a += 3;
    a + b;
    a + 3;
    3 + a;
    std::cout << a; //calls the `operator<<(int)` overload.
}
