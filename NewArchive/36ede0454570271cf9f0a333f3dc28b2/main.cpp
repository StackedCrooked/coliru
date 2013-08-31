#include <iostream>
#include <thread>

template<typename T>
class Rational;

template<typename T>
const Rational<T> doMultiply(const Rational<T>&, const Rational<T>&);

template<typename T> 
class Rational
{
    T m_num;
    T m_den;
public:
    Rational(const T& numerator = 0, const T& denominator = 1) : m_num(numerator), m_den(denominator)
    {}
    
    const T Numerator() const   { return m_num; }
    const T Denominator() const { return m_den; }
    
friend const Rational operator*(const Rational& lhs, const Rational& rhs)
{
    //return doMultiply(lhs, rhs);
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}
};

template<typename T>
const Rational<T> doMultiply(const Rational<T>& lhs, const Rational<T>& rhs)
{
    return Rational<T>(lhs.Numerator()*rhs.Numerator(), lhs.Denominator()*rhs.Denominator());
}

int main()
{
    Rational<int> OneHalf(1,2);
    Rational<int> Result = OneHalf*7;    
    std::cout << std::endl;
    std::cout << "Result = " << Result.Numerator() << "/" << Result.Denominator() << std::endl;
}