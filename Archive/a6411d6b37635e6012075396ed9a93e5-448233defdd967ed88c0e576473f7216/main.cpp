#include <iostream>
#include <boost/operators.hpp>

template<class T>
class wrapper1 
{ 
public:
    wrapper1(T const& t): t_(t) {} // yes, no explicit here
    
    friend wrapper1 operator+(wrapper1 const& lhs, wrapper1 const& rhs)
    {
        return wrapper1{ lhs.t_ + rhs.t_ };        
    }
    
    std::ostream& print(std::ostream& os) const
    {
        return os << t_;
    }
    
private:
    T t_; 
};

template<class T>
std::ostream& operator<<(std::ostream& os, wrapper1<T> const& rhs)
{
    return rhs.print(os);
}

template<class T>
class wrapper2
:
    boost::addable< wrapper2<T> >
{ 
public:
    wrapper2(T const& t): t_(t) {}

    // operator+ provided by boost::addable
    wrapper2& operator+=(wrapper2 const& rhs)
    {
        t_ += rhs.t_;
        return *this;
    }        

    std::ostream& print(std::ostream& os) const
    {
        return os << t_;
    }

private:
    T t_; 
};

template<class T>
std::ostream& operator<<(std::ostream& os, wrapper2<T> const& rhs)
{
    return rhs.print(os);
}

int main()
{
    wrapper1<int> v{1};
    wrapper1<int> w{2};
    
    std::cout << (v + w) << "\n";
    std::cout << (1 + w) << "\n";
    std::cout << (v + 2) << "\n";
        
    wrapper2<int> x{1};
    wrapper2<int> y{2};
    
    std::cout << (x + y) << "\n";
    std::cout << (1 + y) << "\n";
    std::cout << (x + 2) << "\n";
    
}