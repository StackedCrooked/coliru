#include <type_traits>
#include <memory>

class InheritFreeOperators {};

template<typename LHSType, typename RHSType>
auto FreeOpAdd(LHSType&& lhs, RHSType&& rhs, std::true_type, std::true_type) 
-> decltype(std::forward<LHSType>(lhs)+=std::forward<RHSType>(rhs))
{return std::forward<LHSType>(lhs)+=std::forward<RHSType>(rhs);}

template<typename LHSType, typename RHSType>
auto FreeOpAdd(LHSType&& lhs, RHSType&& rhs, std::true_type, std::false_type) 
-> decltype(std::forward<LHSType>(lhs)+=std::forward<RHSType>(rhs))
{return std::forward<LHSType>(lhs)+=std::forward<RHSType>(rhs);}

template<typename LHSType, typename RHSType>
auto FreeOpAdd(LHSType&& lhs, RHSType&& rhs, std::false_type, std::true_type) 
-> decltype(std::forward<RHSType>(rhs)+=std::forward<LHSType>(lhs))
{return std::forward<RHSType>(rhs)+=std::forward<LHSType>(lhs);}

template<typename LHSType, typename RHSType, 
    typename LRaw=typename std::is_base_of<InheritFreeOperators,typename std::decay<LHSType>::type>,
    typename RRaw=typename std::is_base_of<InheritFreeOperators,typename std::decay<RHSType>::type>>
auto operator+(LHSType&& lhs, RHSType&& rhs) 
-> decltype(FreeOpAdd(std::forward<LHSType>(lhs),std::forward<RHSType>(rhs),LRaw{},RRaw{}))
{return FreeOpAdd(std::forward<LHSType>(lhs),std::forward<RHSType>(rhs),LRaw{},RRaw{});}





template<typename Real>
class Interval : private InheritFreeOperators
{
public:
    Interval(Real value)
        : lower(value), upper(value)
    { }

    template<typename Real2>
    Interval(Real2 value)
        : lower(value), upper(value)
    { }

    template<typename Real2>
    Interval(Real2 l, Real2 u)
        : lower(l), upper(u)
    { }

    Interval<Real>& operator += (Interval<Real> rhs)
    {
        lower += rhs.lower;
        upper += rhs.upper;
        return *this;
    }

private:
    Real lower, upper;
};



int main() 
{
    Interval<double> i1(1, 2);
    Interval<double> i2(3, 4);

    i1   + 1.0;
    1.0  + i1;
    i1   + 1.0f;
    1.0f + i1;
    i1   + 1;
    1    + i1;
    i1   + i2;
}