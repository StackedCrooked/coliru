#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <map>

typedef unsigned long long ullong;

struct BigInteger {
   //Base value.
    static const ullong base = 10000;
    //N value
    static const ullong N = 4;

    //Digits holder.
    std::deque<ullong> digits;

    //Default constructors.
    BigInteger();
    BigInteger(std::string str);
    BigInteger(ullong num);

    //Operators
    BigInteger& operator+= (const BigInteger& bi);
    BigInteger& operator-= (const BigInteger& bi);
    BigInteger& operator*= (const BigInteger& bi);
    BigInteger& operator*= (ullong n);
    BigInteger& operator<<= (ullong n);
    BigInteger& operator/= (ullong n);

    BigInteger operator+ (const BigInteger& bi) const;
    BigInteger operator- (const BigInteger& bi) const;
    BigInteger operator* (const BigInteger& bi) const;
    BigInteger operator* (ullong n) const;
    BigInteger operator<< (ullong n) const;

    //Comparison operators
    bool operator== (const BigInteger& other) const;
    bool operator== (ullong other) const;

    //removes all zeroes from the back.
    void normalize();
};

//Helper classes and functors
struct Add { 
    ullong operator()(ullong a, ullong b) { 
        return a + b; 
    } 
};

struct Divide {
    ullong k;
    Divide() {}
    Divide(ullong n): k(n) {}
    ullong operator()(ullong a) {
        return a / k;
    }
};

struct Multiply {
    ullong k;

    Multiply() {}
    Multiply(ullong n): k(n) {}

    ullong operator()(ullong a) { 
        return a * k; 
    }
};

struct Carry {
    ullong& carry;

    Carry(ullong& c): carry(c) {}

    ullong operator()(ullong n)
    {
        n += carry;
        carry = n / BigInteger::base;
        n %= BigInteger::base;

        return n;
    }
};

template <class BaseOperator>
struct OperatorCarry: public BaseOperator, public Carry {
    OperatorCarry(ullong& c): Carry(c) {}

    ullong operator()(ullong a) { 
        return Carry::operator()(BaseOperator::operator()(a)); 
    }
    ullong operator()(ullong a, ullong b) { 
        return Carry::operator()(BaseOperator::operator()(a, b)); 
    }
};

struct Borrow {
    long long& borrow;

    Borrow(long long& b): borrow(b) {}

    ullong operator()(long long n) {
        n -= borrow; 
        borrow = 0;
        while (n < 0) { 
            n += BigInteger::base; 
            ++borrow; 
        }
        return n;
    }
};

struct SubtractionBorrow {
    long long& borrow;

    SubtractionBorrow(long long& b): borrow(b) {}

    ullong operator()(long long a, long long b) {
        long long n = b - a - borrow;
        borrow = 0;
        while (n < 0) { 
            n += BigInteger::base; 
            ++borrow; 
        }
        return n;
    }
};

BigInteger::BigInteger() { 
    digits.assign(1, 0); 
}

BigInteger::BigInteger(ullong num) {
    std::stringstream buffer;
    buffer << num;
    *this = BigInteger(buffer.str());
}

BigInteger::BigInteger(std::string str) {
    std::reverse(str.begin(), str.end());

    while (str.size() % BigInteger::N != 0)
        str.push_back('0');

    std::reverse(str.begin(), str.end());

    ullong position = 0;
    ullong size = str.size();

    while(position != size) {
        std::stringstream buffer(str.substr(position, BigInteger::N));
        ullong digit;
        buffer >> digit;
        digits.push_back(digit);

        position += BigInteger::N;
    }

    std::reverse(digits.begin(), digits.end());
}

BigInteger& BigInteger::operator+= (const BigInteger& bi) {
    if (digits.size() < bi.digits.size())
        digits.resize(bi.digits.size());

    ullong carry = 0;
    std::deque<ullong>::iterator it;

    OperatorCarry<Add> addwc(carry);

    it = std::transform(bi.digits.begin(), bi.digits.end(), digits.begin(), digits.begin(), addwc);

    std::transform(it, digits.end(), it, Carry(carry));

    if(carry) 
        digits.push_back(carry);

    return *this;
}

BigInteger& BigInteger::operator-= (const BigInteger& bi) {
    long long borrow = 0;
    std::deque<ullong>::iterator it;

    it = std::transform(bi.digits.begin(), bi.digits.end(), digits.begin(), digits.begin(), SubtractionBorrow(borrow));

    std::transform(it, digits.end(), it, Borrow(borrow));

    return *this;
}

BigInteger& BigInteger::operator*= (ullong n) {
    ullong carry = 0;

    OperatorCarry<Multiply> mulmc(carry);
    mulmc.k = n;

    std::transform(digits.begin(), digits.end(), digits.begin(), mulmc);

    while(carry) { 
        digits.push_back(carry % BigInteger::base); 
        carry /= BigInteger::base; 
    }

    return *this;
}

BigInteger& BigInteger::operator/=(ullong n) {
    ullong carry = 0;
    OperatorCarry<Divide> divmc(carry);
    divmc.k = n;

    std::transform(digits.begin(),digits.end(),digits.begin(),divmc);
    while(carry) {
        digits.push_back(carry % BigInteger::base);
        carry /= BigInteger::base;
    }

    return *this;
}

BigInteger& BigInteger::operator*= (const BigInteger& bi) {
    const BigInteger* maxOp = this;
    const BigInteger* minOp = &bi;

    ullong maxSize = maxOp->digits.size();
    ullong minSize = minOp->digits.size();

    if (maxSize < minSize) {
        std::swap(maxOp, minOp);
        std::swap(maxSize, minSize);
    }

    std::deque<BigInteger> array(minSize);

    for (ullong i = 0; i < minSize; ++i) {
        array[i].digits.resize(maxSize);
        array[i] = *maxOp * minOp->digits[i];
    }

    *this = array[0];
    digits.resize(maxSize + minSize);

    for (ullong i = 1; i < minSize; ++i) {
        array[i] <<= i;
        *this += array[i];
    }

    return *this;
}

BigInteger& BigInteger::operator<<= (ullong n) {
    digits.resize(digits.size() + n);

    std::copy(digits.rbegin() + n, digits.rend(), digits.rbegin());
    std::fill(digits.begin(), digits.begin() + n, 0);

    return *this;
}

BigInteger BigInteger::operator+ (const BigInteger& bi) const { 
    BigInteger result(*this); 
    return (result  += bi); 
}
BigInteger BigInteger::operator- (const BigInteger& bi) const { 
    BigInteger result(*this); 
    return (result  -= bi); 
}
BigInteger BigInteger::operator* (ullong n) const { 
    BigInteger result(*this); 
    return (result  *=  n); 
}
BigInteger BigInteger::operator* (const BigInteger& bi) const { 
    BigInteger result(*this); 
    return (result  *= bi); 
}
BigInteger BigInteger::operator<< (ullong n) const { 
    BigInteger result(*this); 
    return (result <<=  n); 
}

bool BigInteger::operator== (const BigInteger& other) const {
    return this->digits == other.digits;
}

bool BigInteger::operator== (ullong other) const {
    return *this == BigInteger(other);
}

void BigInteger::normalize() {
    while (digits.size() > 1) {
        if (digits.back() == 0)
            digits.pop_back();
        else 
            break;
    }
}

BigInteger operator+ (ullong n, const BigInteger& bi) { 
    return bi + n; 
}
BigInteger operator* (ullong n, const BigInteger& bi) { 
    return bi * n; 
}

std::ostream& operator<< (std::ostream& out, const BigInteger& bi) {
    BigInteger& bi2 = const_cast<BigInteger&>(bi);
    bi2.normalize();

    long long size = bi.digits.size();

    if (bi.digits[size - 1])
        out << bi.digits[size - 1];

    for(long long i = size - 2; i >= 0; --i) {
        std::stringstream buffer;
        buffer << bi.digits[i];

        std::string str = buffer.str();

        ullong toN = BigInteger::N - str.size();
        if (toN > 0)
            str = std::string(toN, '0') + str;

        out << str;
    }

    return out;
}

BigInteger operator"" _Big(const char* str, std::size_t n) {
    return BigInteger(std::string(str,n));
}

BigInteger operator"" _Big(ullong number) {
    return BigInteger(number);
}


int main() {
    BigInteger a("1092829847819274");
    std::cout << a * 1298471814_Big * "19287488914"_Big;
}
