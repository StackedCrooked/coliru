#include <boost/numeric/ublas/matrix.hpp>
#include <boost/operators.hpp>
#include <iostream>
#include <ostream>
#include <utility>
#include <cstddef>
#include <vector>

using namespace boost;
using namespace std;

class Statistic
{
    size_t ops = 0;
public:
    Statistic &increment()
    {
        ++ops;
        return *this;
    }
    size_t count() const
    {
        return ops;
    }
};

template<typename Domain>
class Profiled: field_operators<Profiled<Domain>>
{
    Domain value;
    static vector<Statistic> stat;
    void stat_increment()
    {
        stat.back().increment();
    }
public:
    struct StatisticScope
    {
        StatisticScope()
        {
            stat.emplace_back();
        }
        Statistic &current()
        {
            return stat.back();
        }
        ~StatisticScope()
        {
            stat.pop_back();
        }
    };
    template<typename ...Args>
    Profiled(Args&& ...args)
        : value{forward<Args>(args)...}
    {}
    Profiled& operator+=(const Profiled& x)
    {
        stat_increment();
        value+=x.value;
        return *this;
    }
    Profiled& operator-=(const Profiled& x)
    {
        stat_increment();
        value-=x.value;
        return *this;
    }
    Profiled& operator*=(const Profiled& x)
    {
        stat_increment();
        value*=x.value;
        return *this;
    }
    Profiled& operator/=(const Profiled& x)
    {
        stat_increment();
        value/=x.value;
        return *this;
    }
};
template<typename Domain>
vector<Statistic> Profiled<Domain>::stat{1};

int main()
{
    typedef Profiled<double> Float;
    {
        Float::StatisticScope s;
        Float x = 1.0, y = 2.0, res = 0.0;
        res = x+y*x+y;
        cout << s.current().count() << endl;
    }
    {
        using namespace numeric::ublas;
        Float::StatisticScope s;
        matrix<Float> x{10, 20},y{20,5},res{10,5};
        res = prod(x,y);
        cout << s.current().count() << endl;
    }
}