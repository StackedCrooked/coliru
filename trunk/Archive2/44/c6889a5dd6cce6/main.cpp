template<typename Real>
class Interval
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
template<typename LHSReal, typename RHSReal> auto operator+(Interval<LHSReal> lhs, const Interval<RHSReal>& rhs) {return lhs+=rhs;}
template<typename Real, typename RHSType> auto operator+(Interval<Real> lhs, const RHSType& rhs) {return lhs+=rhs;}
template<typename Real, typename LHSType> auto operator+(const LHSType& lhs, Interval<Real> rhs) {return rhs+=lhs;}



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