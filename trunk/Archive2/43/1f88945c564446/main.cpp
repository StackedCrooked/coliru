#include <ctime>
#include <chrono>
#include <iostream>

#ifndef LARGEINT_H
#define LARGEINT_H

#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <sstream>

#if (__cplusplus > 199711L || _MSC_VER > 1600)
#include <algorithm>
#include <cmath>
#include <cstring>
#include <type_traits>
#else
#include <string.h>
#include <math.h>
#endif


#ifdef _WIN32
namespace patch {
    template <typename T>
    std::string to_string(T value)
    {
        std::ostringstream os;
    	os << value ;
    	return os.str() ;
    }    
}
#endif

class LargeInt {
public:
    //Constructors
    LargeInt();
    LargeInt(const char* str);
    LargeInt(const std::string& str);
    template <typename T>
    LargeInt(T t);
public:
    //Assigment operators
    const LargeInt& operator=(const char* str);
    const LargeInt& operator=(const std::string& str);
    template <typename T>
    const LargeInt& operator=(T t);

    //Unary
    const LargeInt& operator++();
    const LargeInt& operator--();
    LargeInt operator++(int);
    LargeInt operator--(int);
public:
    //Operations
    const LargeInt& operator+=(const LargeInt& rhs);
    const LargeInt& operator-=(const LargeInt& rhs);
    const LargeInt& operator*=(const LargeInt& rhs);
    const LargeInt& operator/=(const LargeInt& rhs);
    const LargeInt& operator%=(const LargeInt& rhs);
    template <typename T>
    const LargeInt& operator*=(T rhs);

    LargeInt operator-() const;
    LargeInt operator+(const LargeInt& rhs) const;
    LargeInt operator-(const LargeInt& rhs) const;
    LargeInt operator*(const LargeInt& rhs) const;
    LargeInt operator/(const LargeInt& rhs) const;
    LargeInt operator%(const LargeInt& rhs) const;
    template <typename T>
    LargeInt operator*(T rhs) const;
public:
    //Logical
    bool operator==(const LargeInt& rhs) const;
    bool operator!=(const LargeInt& rhs) const;
    bool operator<(const LargeInt& rhs) const;
    bool operator<=(const LargeInt& rhs) const;
    bool operator>(const LargeInt& rhs) const;
    bool operator>=(const LargeInt& rhs) const;
public:
    //Needed methods
    std::string toString() const;
    LargeInt power(const int pow);
    LargeInt square() const;
public:
    //Interface values
    static const LargeInt zero;
    static const LargeInt one;
private:
    //Needed private methods
    static int findD(const LargeInt& R, const LargeInt& D);
    static void digitIncrement(int factor, std::vector<int>& val);

    void stringToLargeInt(const std::string& str);

    template <typename T>
    void convertT(T t);
    void remake(bool lead = false, bool vsign = false);

    bool determineSize();
    void truncateToBase();
private:
    //Number information variables
    std::vector<int> number;
    bool sign;
private:
    //Output overloads
    friend std::ostream& operator<<(std::ostream &s, const LargeInt &n);
    friend std::istream& operator>>(std::istream &s, LargeInt &n);
};

const LargeInt LargeInt::zero = 0;
const LargeInt LargeInt::one = 1;

/**
 * Constructors
 */
LargeInt::LargeInt() : sign(true) {
    number.push_back(0);
}

LargeInt::LargeInt(const char* str) {
    stringToLargeInt(str);
}

LargeInt::LargeInt(const std::string& str) {
    stringToLargeInt(str);
}

template <typename T>
LargeInt::LargeInt(T t) {
    convertT(t);
}

/**
 * Assigment operators
 */
const LargeInt& LargeInt::operator=(const char* str) {
    stringToLargeInt(str);
    return *this;
}

const LargeInt& LargeInt::operator=(const std::string& str) {
    stringToLargeInt(str);
    return *this;
}

template <typename T>
const LargeInt& LargeInt::operator=(T t) {
    convertT(t);
    return *this;
}

/**
 * Unary
 */
const LargeInt& LargeInt::operator++() {
    number[0] += (sign ? 1 : -1);
    remake(false, true);
    return *this;
}

const LargeInt& LargeInt::operator--() {
    number[0] -= (sign ? 1 : -1);
    remake(false, true);
    return *this;
}

LargeInt LargeInt::operator++(int) {
    LargeInt result = *this;
    number[0] += (sign ? 1 : -1);
    remake(false, true);
    return result;
}

LargeInt LargeInt::operator--(int) {
    LargeInt result = *this;
    number[0] -= (sign ? 1 : -1);
    remake(false, true);
    return result;
}

/**
 * Operations
 */
const LargeInt& LargeInt::operator+=(const LargeInt& rhs) {
    const int nSize = number.size();
    const int rnSize = rhs.number.size();

    if (rnSize > nSize) {
        number.resize(rnSize, 0);
    }
    for (int i = 0; i < nSize; ++i) {
        const int rem = (i < rnSize ? (rhs.sign ? rhs.number[i] : -rhs.number[i]) : 0);
        const int sig = (sign ? number[i] : -number[i]);
        number[i] = sig + rem;
    }
    remake();
    return *this;
}

const LargeInt& LargeInt::operator-=(const LargeInt& rhs) {
    const int nSize = number.size();
    const int rnSize = rhs.number.size();

    if (rnSize > nSize) {
        number.resize(rnSize, 0);
    }
    for (int i = 0; i < nSize; ++i) {
        const int rem = (i < rnSize ? (rhs.sign ? rhs.number[i] : -rhs.number[i]) : 0);
        const int seg = (sign ? number[i] : -number[i]);
        number[i] = seg - rem;
    }
    remake();
    return *this;
}

const LargeInt& LargeInt::operator*=(const LargeInt& rhs) {
    *this = *this * rhs;
    return *this;
}

const LargeInt& LargeInt::operator/=(const LargeInt& rhs) {
    if (rhs == zero) {
        std::cerr << "Division by zero!" << std::endl;
        return *this;
    }
    LargeInt R;
    LargeInt D = (rhs.sign ? rhs : -rhs);
    LargeInt N = (sign ? *this : -*this);

    bool oSign = sign;
    number.clear();
    number.resize(N.number.size(), 0);

    int i = static_cast<int>(N.number.size()) - 1;
    for (; i >= 0; --i) {
        R.number.insert(R.number.begin(), 0);
        R.number[0] = N.number[i];
        R.remake(true);
        int cnt = findD(R, D);
        R -= D * cnt;
        number[i] += cnt;
    }
    remake();
    sign = (number.size() == 1 && number[0] == 0) ? true : (oSign == rhs.sign);
    return *this;
}

const LargeInt& LargeInt::operator%=(const LargeInt& rhs) {
    if (rhs == zero) {
        std::cerr << "Division by zero!" << std::endl;
        return zero;
    }
    LargeInt D = (rhs.sign ? rhs : -rhs);
    LargeInt N = (sign ? *this : -*this);

    bool oSign = sign;
    number.clear();

    int i = static_cast<int>(N.number.size()) - 1;
    for (; i >= 0; --i) {
        number.insert(number.begin(), 0);
        number[0] = N.number[i];
        remake(true);
        *this -= D * findD(*this, D);
    }
    remake();
    sign = (number.size() == 1 && number[0] == 0) ? true : oSign;
    return *this;
}

template <typename T>
const LargeInt& LargeInt::operator*=(T rhs) {
    int factor = rhs < 0 ? -rhs : rhs;
    bool oSign = sign;
    digitIncrement(factor, number);
    remake();
    sign = (number.size() == 1 && number[0] == 0) ? true : (oSign == (rhs >= 0));
    return *this;
}

LargeInt LargeInt::operator-() const {
    LargeInt result = *this;
    result.sign = !sign;
    return result;
}

LargeInt LargeInt::operator+(const LargeInt& rhs) const {
    const auto nSize = number.size();
    const auto rnSize = rhs.number.size();
    LargeInt result;

    result.number.resize(nSize > rnSize ? nSize : rnSize, 0);
    for (unsigned int i = 0; i < nSize || i < rnSize; ++i) {
        result.number[i] = (i < nSize ? (sign ? number[i] : -number[i]) : 0) + (i < rnSize ? (rhs.sign ? rhs.number[i] : -rhs.number[i]) : 0);
    }
    result.remake();
    return result;
}

LargeInt LargeInt::operator-(const LargeInt& rhs) const {
    const auto nSize = number.size();
    const auto rnSize = rhs.number.size();
    LargeInt result;

    result.number.resize(nSize > rnSize ? nSize : rnSize, 0);
    for (unsigned int i = 0; i < nSize || i < rnSize; ++i) {
        result.number[i] = (i < nSize ? (sign ? number[i] : -number[i]) : 0) - (i < rnSize ? (rhs.sign ? rhs.number[i] : -rhs.number[i]) : 0);
    }
    result.remake();
    return result;
}

LargeInt LargeInt::operator*(const LargeInt& rhs) const {
    const int nSize = number.size();
    const int rnSize = rhs.number.size();
#if (__cplusplus > 199711L || _MSC_VER > 1600)
    const int baseDivisor = static_cast<int>(std::pow(10,9));
#else
    const int baseDivisor = static_cast<int>(pow(10,9));
#endif

    LargeInt result;
    result.number.resize(nSize + rnSize, 0);
    long long carry = 0;
    auto digit = 0;

    for (;; ++digit) {

        long long oldcarry = carry;
        carry /= baseDivisor;
        result.number[digit] = static_cast<int>(oldcarry - carry * baseDivisor);

        bool found = false;
        for (int i = digit < rnSize ? 0 : digit - rnSize + 1; i < nSize && i <= digit; ++i) {
            long long pval = result.number[digit] + number[i] * static_cast<long long>(rhs.number[digit - i]);
            if (pval >= baseDivisor || pval <= -baseDivisor) {
                long long quot = pval / baseDivisor;
                carry += quot;
                pval -= quot * baseDivisor;
            }
            result.number[digit] = static_cast<int>(pval);
            found = true;
        }
        if (!found) {
            break;
        }
    }
    for (; carry > 0; ++digit) {
        result.number[digit] = static_cast<int>(carry % baseDivisor);
        carry /= baseDivisor;
    }
    result.remake();
    result.sign = (result.number.size() == 1 && result.number[0] == 0) ? true : (sign == rhs.sign);
    return result;
}

LargeInt LargeInt::operator/(const LargeInt& rhs) const {
    if (rhs == zero) {
        std::cerr << "Division by zero!" << std::endl;
        return zero;
    }
    LargeInt Q;
    LargeInt R;
    LargeInt D = (rhs.sign ? rhs : -rhs);
    LargeInt N = (sign ? *this : -*this);

    Q.number.resize(N.number.size(), 0);
    for (int i = static_cast<int>(N.number.size()) - 1; i >= 0; --i) {
        R.number.insert(R.number.begin(), 0);
        R.number[0] = N.number[i];
        R.remake(true);
        int cnt = findD(R, D);
        R -= D * cnt;
        Q.number[i] += cnt;
    }
    Q.remake();
    Q.sign = (Q.number.size() == 1 && Q.number[0] == 0) ? true : (sign == rhs.sign);
    return Q;
}

LargeInt LargeInt::operator%(const LargeInt& rhs) const {
    if (rhs == zero) {
        std::cerr << "Division by zero!" << std::endl;
        return zero;
    }
    LargeInt R;
    LargeInt D = (rhs.sign ? rhs : -rhs);
    LargeInt N = (sign ? *this : -*this);
    for (int i = static_cast<int>(N.number.size()) - 1; i >= 0; --i) {
        R.number.insert(R.number.begin(), 0);
        R.number[0] = N.number[i];
        R.remake(true);
        R -= D * findD(R, D);
    }
    R.remake();
    R.sign = (R.number.size() == 1 && R.number[0] == 0) ? true : sign;
    return R;
}

template <typename T>
LargeInt LargeInt::operator*(T rhs) const {
    LargeInt result = *this;
    int factor = rhs < 0 ? -rhs : rhs;
    digitIncrement(factor, result.number);
    result.remake();
    result.sign = (result.number.size() == 1 && result.number[0] == 0) ? true : (sign == (rhs >= 0));
    return result;
}

/**
 * Logical
 */
bool LargeInt::operator==(const LargeInt& rhs) const {
    const int nSize = number.size();
    const int rnSize = rhs.number.size();

    if (sign != rhs.sign || nSize != rnSize) {
        return false;
    }
    for (int i = nSize - 1; i >= 0; --i) {
        if (number[i] != rhs.number[i]) {
            return false;
        }
    }
    return true;
}

bool LargeInt::operator!=(const LargeInt& rhs) const {
    return !(*this == rhs);
}

bool LargeInt::operator<(const LargeInt& rhs) const {
    const int nSize = number.size();
    const int rnSize = rhs.number.size();

    if (sign && !rhs.sign) {
        return false;
    }
    if (!sign && rhs.sign) {
        return true;
    }
    if (nSize > rnSize) {
        return !sign;
    }
    if (nSize < rnSize) {
        return sign;
    }
    for (int i = nSize - 1; i >= 0; --i) {
        if (number[i] < rhs.number[i]) {
            return sign;
        }
        if (number[i] > rhs.number[i]) {
            return !sign;
        }
    }
    return false;
}

bool LargeInt::operator<=(const LargeInt& rhs) const {
    return (*this < rhs);
}

bool LargeInt::operator>(const LargeInt& rhs) const {
    return !(*this < rhs);
}

bool LargeInt::operator>=(const LargeInt& rhs) const {
    return !(*this < rhs);
}

/**
 * Needed methods
 */
std::string LargeInt::toString() const {
    std::string str = "";
    for (const auto& e : number) {
#ifndef _WIN32
        str += std::to_string(e);
#else
        str += patch::to_string(e);
#endif
    }
    return str;
}

LargeInt LargeInt::power(const int pow) {
    for (int i = 0; i < pow; i++) {
        *this *= *this;
    }
    return *this;
}

LargeInt LargeInt::square() const {
    LargeInt re;

    if (!sign) {
        return re;
    }

    while (true) {
        re += 1;

        LargeInt b = re * re;
        if (b == *this) {
            return re;
        }
        else if (b > *this) {
            break;
        }
    }
    return re;
}

/**
 * Needed private methods
 */
int LargeInt::findD(const LargeInt& R, const LargeInt& D) {
    int min = 0;
    int max = 999999999;

    while (max - min > 0) {
        int avg = max + min;
        int havg = avg / 2;

        avg = avg - havg * 2 ? (havg + 1) : havg;
        LargeInt prod = D * avg;

        if (R == prod) {
            return avg;
        }
        else if (R > prod) {
            min = avg;
        }
        else {
            max = avg - 1;
        }
    }

    return min;
}

void LargeInt::digitIncrement(int factor, std::vector<int>& val) {
#if (__cplusplus > 199711L || _MSC_VER > 1600)
    const int baseDivisor = static_cast<int>(std::pow(10,9));
#else
    const int baseDivisor = static_cast<int>(pow(10,9));
#endif

    int carry = 0;
    for (unsigned int i = 0; i < val.size(); ++i) {
        long long pval = val[i] * static_cast<long long>(factor) + carry;

        if (pval >= baseDivisor || pval <= -baseDivisor) {

            carry = static_cast<int>(pval / baseDivisor);
            pval -= carry * baseDivisor;
        }
        else {
            carry = 0;
        }
        val[i] = static_cast<int>(pval);
    }
    if (carry > 0) {
        val.push_back(carry);
    }
}

void LargeInt::stringToLargeInt(const std::string &str) {
    sign = true;
    number.clear();

    number.reserve(str.size() / 9 + 1);
    int i = static_cast<int>(str.size()) - 9;

    for (; i >= 0; i -= 9) {
        number.push_back(std::stoi(str.substr(i, 9)));
    }

    if (i > -9) {
        std::string strs = str.substr(0, i + 9);

        if (strs.size() == 1 && strs[0] == '-') {
            sign = false;
        }
        else {
            number.push_back(std::stoi(strs));
        }
    }
    if (number.back() < 0) {
        number.back() = -number.back();
        sign = false;
    }
    remake(true);
}

template <typename T>
void LargeInt::convertT(T t) {
#if __cplusplus > 199711L
    static_assert(std::is_integral<T>() || std::is_floating_point<T>(), "Invalid argument for convertT");
#endif
    sign = (t >= 0);

#if (__cplusplus > 199711L || _MSC_VER > 1600)
    const int baseDivisor = static_cast<int>(std::pow(10,9));
#else
    const int baseDivisor = static_cast<int>(pow(10,9));
#endif
    
    if (!sign) {
        t = -t;
    }

    do {
        std::div_t divR = div(t,baseDivisor);
        number.push_back(divR.rem);
        t = divR.quot;
    }
    while (t > 0);
}

void LargeInt::remake(bool lead, bool vsign) {
    if (!lead) {
        truncateToBase();

        if (determineSize()) {
            sign = ((number.size() == 1 && number[0] == 0) || !vsign) ? true : sign;
        }
        else {
            sign = vsign ? !sign : false;
            for (unsigned int i = 0; i < number.size(); ++i) {
                number[i] = std::abs(number[i]);
            }
        }
    }
    for (int i = static_cast<int>(number.size()) - 1; i > 0; --i) {
        if (number[i] != 0) {
            return;
        }
        else {
            number.erase(number.begin() + i);
        }
    }
}

bool LargeInt::determineSize() {
    bool isPositive = true;
    int i = static_cast<int>((number.size())) - 1;
#if (__cplusplus > 199711L || _MSC_VER > 1600)
    const int baseDivisor = static_cast<int>(std::pow(10,9));
#else
    const int baseDivisor = static_cast<int>(pow(10,9));
#endif
    const int max = 999999999;

    for (;i >= 0; --i) {
        if (number[i] != 0) {
            isPositive = number[i--] > 0;
            break;
        }
    }

    if (isPositive) {
        for (;i >= 0; --i) {
            if (number[i] < 0) {
                int k = 0, index = i + 1;

                for (;static_cast<size_t>(index) < number.size() && number[index] == 0; ++k, ++index); {
                    number[index] -= 1;
                    number[i] += baseDivisor;

                    for (;k > 0; --k) {
                        number[i + k] = max;
                    }
                }
            }
        }
    }
    else {
        for (;i >= 0; --i) {
            if (number[i] > 0) {
                int k = 0, index = i + 1;
                for (;static_cast<size_t>(index) < number.size() && number[index] == 0; ++k, ++index); {
                    number[index] += 1;
                    number[i] -= baseDivisor;

                    for (;k > 0; --k) {
                        number[i + k] = -max;
                    }
                }
            }
        }
    }

    return isPositive;
}

void LargeInt::truncateToBase() {
#if (__cplusplus > 199711L || _MSC_VER > 1600)
    const int baseDivisor = static_cast<int>(std::pow(10,9));
#else
    const int baseDivisor = static_cast<int>(pow(10,9));
#endif

    for (unsigned int i = 0; i < number.size(); ++i) {
        if (number[i] >= baseDivisor || number[i] <= -baseDivisor) {
            div_t dt = div(number[i], baseDivisor);
            number[i] = dt.rem;

            if (i + 1 >= number.size()) {
                number.push_back(dt.quot);
            }
            else {
                number[i + 1] += dt.quot;
            }
        }
    }
}

/**
 * Output overloads
 */
inline std::istream& operator>>(std::istream &s, LargeInt &n) {
    std::string str;
    s >> str;
    n.stringToLargeInt(str);
    return s;
}

inline std::ostream& operator<<(std::ostream &s, const LargeInt &n) {
    if (!n.sign) {
        s << '-';
    }
    bool first = true;

    for (int i = static_cast<int>(n.number.size()) - 1; i >= 0; --i) {
        if (first) {
            s << n.number[i];
            first = false;
        }
        else {
            s << std::setfill('0') << std::setw(9) << n.number[i];
        }
    }
    return s;
}

#endif // LARGEINT_H

//LargeInt SumOfDivisors(LargeInt num)
//{
//    LargeInt sum = 0;
//    const LargeInt numDiv2 = num / 2;
//    for(LargeInt i = 1; i * i <= num; i++)
//    	sum += (num % i == 1) ? 0 
//                    : ((i * i == num) ? i 
//                        : i + num / i);
//    return sum;
//}

static LargeInt LeastPower(LargeInt a, LargeInt x)
{
    LargeInt b = a;
    while (x % b == 0)
        b *= a;
    return b;
}


static LargeInt SumDivisors(LargeInt x)
{
    LargeInt t = x;
    LargeInt result = 1;

    LargeInt p = LeastPower(2, t);
    result *= p-1;
    t /= p / 2;

    for (LargeInt i = 3; i * i <= t; i += 2) {
        LargeInt p = LeastPower(i, t);
        result *= (p - 1) / (i - 1);
        t /= p / i;
    }

    if (LargeInt::one < t)
        result *= LargeInt::one + t;

    return result - x;
}

int main() {
    //10^60
    const LargeInt n("1000000000000000000000000000000000000000000000000000000000000");
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    
    //const LargeInt a = SumOfDivisors(n);
    const LargeInt a = SumDivisors(n) + n;
    
    end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
              
    std::cout << "Sum of divisors for (" << n << ") = " << a << std::endl;
}





