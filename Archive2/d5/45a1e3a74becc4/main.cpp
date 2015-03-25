#include <type_traits>
#include <iostream>

namespace
{
    class Foo
    {
    public:
    
        explicit Foo(long value): m_value(value)
        {}
        
        operator double() const
        {
            std::cout << "Converting to double.." << std::endl;
            return 1.*m_value;
        }
        
        Foo operator+(const Foo& rhs) const
        {
            std::cout << "Adding Foo..." << std::endl;
            Foo res(*this);
            res.m_value += rhs.m_value;
            return res;
        }
        
        template< class T, class=typename std::enable_if<std::is_integral<T>::value>::type>
        Foo operator+(const T n) const
        {
            std::cout << "Adding integral type..." << std::endl; 
            Foo res(*this);
            res.m_value += n;
            return res;
        }
        
        friend std::ostream& operator << (std::ostream& os, const Foo& x);
        
    private:
        
        long m_value;
    };
    
    std::ostream& operator << (std::ostream& os, const Foo& x)
    {
        os << "[" << x.m_value << "]";
        return os;
    }
}

int main()
{
    Foo x(1);
    Foo y(2);
    
    std::cout << x + y << " " << x + 10L << " " << x + 0.3 << std::endl;
}
