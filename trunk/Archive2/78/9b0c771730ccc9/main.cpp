#include <cstdint>

template <class T, int64_t modulus>
class Modular {
public:
    Modular() : num_(0) { }
    Modular(const T& num = 0) : num_(num % modulus) { }
    Modular(const Modular& other) : num_(other.num_) { }
    ~Modular() { }

    T get() const { return num_; }

    Modular& operator=(const Modular& other) { num_ = other.num_; return *this; }
    bool operator==(const Modular& other) { return num_ == other.num_; }
    bool operator!=(const Modular& other) { return num_ != other.num_; }
    Modular& operator++() { ++num_; num_ %= modulus; return *this; }
    Modular operator++(int) { Modular temp(*this); operator++(); return temp; }
    Modular& operator+=(const Modular& other) { num_ += other.num_; num_ %= modulus; return *this; }
    Modular& operator-=(const Modular& other) { num_ -= other.num_; num_ %= modulus; return *this; }
    Modular& operator*=(const Modular& other) { num_ *= other.num_; num_ %= modulus; return *this; }

    Modular& operator/=(const Modular& other)
    {
        if((num_ % other.num_) == 0)
            num_ /= other.num_;
        else
        {
            Modular temp(0);
            while(temp * other != num_)
                ++temp;
            num_ = temp.num_;
        }

        return *this;
    }

    Modular pow(const T& exp)
    {
        if(exp == 1)
            return *this;

        Modular square(num_ * num_ % modulus);

        if(exp & 1)
            return (*this) * square.pow(exp/2);
        else
            return square.pow(exp/2);
    }

protected:
    T num_;
};

template <class T, int64_t modulus>
inline Modular<T, modulus> operator+(const Modular<T, modulus>& lhs, const Modular<T, modulus>& rhs)
{
    Modular<T, modulus> temp(lhs);
    temp += rhs;
    return temp;
}

template <class T, int64_t modulus>
inline Modular<T, modulus> operator-(const Modular<T, modulus>& lhs, const Modular<T, modulus>& rhs)
{
    Modular<T, modulus> temp(lhs);
    temp -= rhs;
    return temp;
}

template <class T, int64_t modulus>
inline Modular<T, modulus> operator*(const Modular<T, modulus>& lhs, const Modular<T, modulus>& rhs)
{
    Modular<T, modulus> temp(lhs);
    temp *= rhs;
    return temp;
}

template <class T, int64_t modulus>
inline Modular<T, modulus> operator/(const Modular<T, modulus>& lhs, const Modular<T, modulus>& rhs)
{
    Modular<T, modulus> temp(lhs);
    temp /= rhs;
    return temp;
}



#include <iostream>
#include <array>
#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::int128_t;

int main()
{
    const int128_t n = 123;
    const int64_t mod = 456;

    typedef Modular<int128_t, mod> mint;

    const mint a(789);
    const mint b(12);

    mint result(0);

    //for(mint x(1); x != mint(101); ++x){
    mint x(1);
        result += (a * x.pow(n+2) + b * x.pow(n+1) - x) / mint(x*x + x - mint(1));
    //}
    std::cout << result.get();

    return 0;
}
