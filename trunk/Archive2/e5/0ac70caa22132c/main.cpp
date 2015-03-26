#include <type_traits>
#include <iostream>

namespace
{
    class Ratio
    {
    public:
    
        explicit Ratio(long num, long den): m_num(num), m_den(den)
        {}
        
        operator double() const
        {
            std::cout << "Converting to double.." << std::endl;
            return static_cast<double>(m_num)/m_den;
        }
        
        Ratio operator+(const Ratio& rhs) const
        {
            std::cout << "Adding Ratio..." << std::endl;
            long num = m_num*rhs.m_den + m_den*rhs.m_num;
            long den = m_den*rhs.m_den;
            return Ratio(num, den);
        }
        
        template<typename T>
        typename std::enable_if<std::is_integral<T>::value, Ratio>::type operator+(const T n) const
        {
            std::cout << "Adding integral type..." << std::endl;
            Ratio res(*this);
            res.m_num += n*m_den;
            return res;
        }
        
        friend std::ostream& operator << (std::ostream& os, const Ratio& x);
        
    private:
        
        long m_num;
        long m_den;
    };
    
    std::ostream& operator << (std::ostream& os, const Ratio& x)
    {
        os << "[" << x.m_num << "/" << x.m_den << "]";
        return os;
    }
}

int main()
{
    Ratio x(1, 3);
    Ratio y(2, 5);
    
    std::cout << x + y << " " << x + 10L << " " << x + 0.3 << " " << x + 3 + 1.7 <<  std::endl;
}
