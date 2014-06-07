#include <boost/icl/gregorian.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <iostream>
#include <iterator>

namespace icl = boost::icl;

struct record {
    std::string name;

    using ptime = boost::posix_time::ptime;
    ptime added, removed;

    icl::interval<ptime>::interval_type validity() const { 
        icl::interval<ptime> x;
        return x.right_open(added, removed);
    }

    friend std::ostream& operator<<(std::ostream& os,const record& r) {
        return os << "{" << r.name << ", " << r.added << ", " << r.removed << "}";
    }
};

int main()
{
    using namespace boost::gregorian;
    using namespace boost::posix_time;

    ptime const start(day_clock::local_day(), { });

    std::vector<record> L {
        { "long"     , start + hours(77) , start + days(7) }   ,
        { "medium"   , start + hours(200), start + hours(236) },
        { "short"    , start + hours(220), start + hours(226) },
        { "ephemeral", start + hours(100), start + hours(101) },
    };

    for (ptime T = start; T <= (start + days(10)); T += hours(6))
    {
        std::cout << "\nT:" << T << "\t";
        std::ostream_iterator<record> out(std::cout, ";");
        std::copy_if(L.begin(), L.end(), out, [T](record const& r) { return icl::contains(r.validity(), T); });
    }
}
