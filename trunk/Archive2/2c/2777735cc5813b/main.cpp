#include <vector>
#include <iostream>

#include <array>
#include <cstdlib>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <ostream>

template <typename T, unsigned N>
class MultivariatePolynomial
{
public:
    typedef MultivariatePolynomial<T, N> SelfType;
    typedef std::array<int, N> Monomial;
    typedef std::map<Monomial, T> Coeffs;
    typedef std::array<T, N> Values;

public:
    MultivariatePolynomial(const T& coeff)
    {
        if (coeff != T(0)) {
            const Monomial m = {T(0)};
            m_coeffs.insert(std::make_pair(m, coeff));
        }
    }

    MultivariatePolynomial(const Coeffs& coeffs)
    {
        for(const auto& p : coeffs) {
            if (p.second != T(0)) {
                m_coeffs.insert(p);
            }
        }
    }

    bool operator==(const SelfType& other) const
    {
        return m_coeffs == other.m_coeffs;
    }

    bool operator!=(const SelfType& other) const
    {
        return m_coeffs != other.m_coeffs;
    }

    SelfType operator+(const SelfType& other) const
    {
        SelfType result(*this);
        result += other;
        return result;
    }

    SelfType operator-(const SelfType& other) const
    {
        SelfType result(*this);
        result -= other;
        return result;
    }

    SelfType& operator+=(const SelfType& other)
    {
        for(const auto& p : other.m_coeffs) {
            AddMonomial(p);
        }

        return *this;
    }

    SelfType& operator-=(const SelfType& other)
    {
        for(const auto& p : other.m_coeffs) {
            SubMonomial(p);
        }

        return *this;
    }

    SelfType operator-() const
    {
        SelfType result(*this);
        for(auto& p : result.m_coeffs) {
            p.second *= T(-1);
        }
        return result;
    }

    SelfType operator*(const SelfType& other) const
    {
        SelfType result;
        for(const auto& p1 : m_coeffs) {
            for(const auto& p2 : other.m_coeffs) {
                result.AddMonomial(MulMonomial(p1, p2));
            }
        }

        return result;
    }

    SelfType& operator*=(const SelfType& other)
    {
        *this = ((*this) * other);
        return *this;
    }

    int Degree() const
    {
        if (m_coeffs.empty()) {
            return -1;
        }

        int maxD = std::numeric_limits<int>::min();
        for(const auto& p : m_coeffs) {
            const auto& m = p.first;
            const int mDegree = std::accumulate(m.begin(), m.end(), 0);
            maxD = std::max(maxD, mDegree);
        }

        return maxD;
    }

    T operator()(const Values& values) const
    {
        T result(0);
        for(const auto& p : m_coeffs) {
            result += Calculate(p, values);
        }

        return result;
    }

    friend std::ostream& operator<<(std::ostream& output, const SelfType& poly)
    {
        if (poly.m_coeffs.empty()) {
            return output;
        }

        auto it = poly.m_coeffs.rbegin();
        PrintMonomial(output, *it);
        for(++it; it != poly.m_coeffs.rend(); ++it) {
            if (it->second > T(0)) {
                output << '+';
            }
            PrintMonomial(output, *it);
        }

        return output;
    }

    typedef typename Coeffs::const_iterator MapIter;

    class CoeffIterator : public std::iterator<typename MapIter::iterator_category, const T>
    {
    public:
        CoeffIterator(const MapIter& it)
            : m_it(it)
        {
        }

        CoeffIterator& operator++()
        {
            ++m_it;
            return *this;
        }

        CoeffIterator operator++(int)
        {
            CoeffIterator temp(*this);
            ++m_it;
            return temp;
        }

        CoeffIterator& operator--()
        {
            --m_it;
            return *this;
        }

        CoeffIterator operator--(int)
        {
            CoeffIterator temp(*this);
            --m_it;
            return temp;
        }

        const T& operator*() const
        {
            return m_it->second;
        }

        const T* operator->() const
        {
            return &m_it->second;
        }

    private:
        MapIter m_it;
    };


    CoeffIterator BeginCoeffIter() const
    {
        return CoeffIterator(m_coeffs.begin());
    }

    CoeffIterator EndCoeffIter() const
    {
        return CoeffIterator(m_coeffs.end());
    }

private:
    MultivariatePolynomial()
    {
    }

    typedef typename Coeffs::value_type MonCoeff;

    void AddMonomial(const MonCoeff& p)
    {
        const auto& r = m_coeffs.insert(p);
        if (!r.second) {
            auto& iter = r.first;
            iter->second += p.second;
            if (iter->second == T(0)) {
                m_coeffs.erase(iter);
            }
        }
    }

    void SubMonomial(const MonCoeff& p)
    {
        const auto& r = m_coeffs.insert(p);
        if (!r.second) {
            auto& iter = r.first;
            iter->second -= p.second;
            if (iter->second == T(0)) {
                m_coeffs.erase(iter);
            }
        }
    }

    static MonCoeff MulMonomial(const MonCoeff& a, const MonCoeff& b)
    {
        Monomial mon;
        for (unsigned i = 0; i < N; ++i) {
            mon[i] = a.first[i] + b.first[i];
        }

        return MonCoeff(mon, a.second * b.second);
    }

    static T Calculate(const MonCoeff& a, const Values& values)
    {
        T result = a.second;
        const auto& degrees = a.first;
        for(unsigned i = 0; i < N; ++i) {
            if (degrees[i] != 0) {
                result *= CalculatePow(values[i], degrees[i]);
            }
        }

        return result;
    }

    static T CalculatePow(const T& value, const int degree)
    {
        T result(1);
        for(int i = 0; i < degree; ++i) {
            result *= value;
        }

        return result;
    }

    static void PrintMonomial(std::ostream& output, const MonCoeff& a)
    {
        if (IsEmptyMonomial(a.first)) {
            output << a.second;
            return;
        }

        if (a.second == T(-1)) {
            output << '-';
        } else if (a.second != T(1)) {
            output << a.second << '*';
        }

        unsigned i = 0;
        for(; a.first[i] == 0; ++i);
        PrintVariable(output, a.first[i], i);
        for(++i; i < N; ++i) {
            if (a.first[i] != 0) {
                output << '*';
                PrintVariable(output, a.first[i], i);
            }
        }
    }

    static void PrintVariable(std::ostream& output, int degree, unsigned index)
    {
        output << 'x' << index;
        if (degree != 1) {
            output << '^' << degree;
        }
    }

    static bool IsEmptyMonomial(const Monomial& m)
    {
        for(auto degree : m) {
            if (degree != 0) {
                return false;
            }
        }

        return true;
    }

private:
    Coeffs m_coeffs;
};



int main() {
    constexpr int N = 3;
    typedef std::array<int, N> Monomial;
    

    typedef int T;
    std::map<Monomial, T> coeffs;

    Monomial mon1 = {3, 0, 1};
    T coeff1 = -5;
    coeffs.insert(std::make_pair(mon1, coeff1));

    Monomial mon2 = {0, 0, 2};
    T coeff2 = 1;
    coeffs.insert(std::make_pair(mon2, coeff2));

    Monomial mon3 = {0, 1, 0};
    T coeff3 = -1;
    coeffs.insert(std::make_pair(mon3, coeff3));

    MultivariatePolynomial<T, N> p(coeffs);
    std::cout << p;

/*
    coeffs.clear();
    std::cin >> n;
    while (n-->0) {
        for (size_t i = 0; i != N; ++i)
            std::cin >> mon[i];
        std::cin >> coeffs[mon];
    }
    MultivariatePolynomial<T, N> q(coeffs);

    std::cout << "p(x) = " << p << "\n";
    std::cout << "q(x) = " << q << "\n";

    std::cout << "deg p = " << p.Degree() << "\n";
    std::cout << "deg q = " << q.Degree() << "\n";

    std::cout << "p(x) + q(x) = " << (p + q) << "\n";
    std::cout << "p(x) - q(x) = " << (p - q) << "\n";
    std::cout << "p(x) * q(x) = " << (p * q) << "\n";

    Monomial x;
    for (size_t i = 0; i != N; ++i)
        x[i] = 0;
    std::cout << "p(0,...,0) = " << p(x) << "\n";
    std::cout << "q(0,...,0) = " << q(x) << "\n";

    for (size_t i = 0; i != N; ++i)
        x[i] = i + 1;
    std::cout << "p(1,...,n) = " << p(x) << "\n";
    std::cout << "q(1,...,n) = " << q(x) << "\n";

    auto f = p - q;
    (f -=p );
    f *= -1;
    std::cout << "Testing +=, -=, *=, == and !=: " << (f == q) << " " << (f != q) << " " << (f - q == 0) << "\n";
    */
}

