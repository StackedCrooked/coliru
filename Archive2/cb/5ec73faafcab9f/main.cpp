#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/split_free.hpp>

#include <boost/icl/discrete_interval.hpp>
#include <boost/icl/interval_set.hpp>

namespace boost { namespace serialization {

    template <typename Archive, typename V>
        void save(Archive& ar, boost::icl::discrete_interval<V> const& di, unsigned) {
            auto const& bb = di.bounds().bits();
            auto const& l  = di.lower();
            auto const& u  = di.upper();

            ar << bb << l << u;
        }

    template <typename Archive, typename V>
        void load(Archive& ar, boost::icl::discrete_interval<V>& di, unsigned) {
            auto bb = di.bounds().bits();
            V    l, u;

            ar >> bb >> l >> u;

            di = boost::icl::discrete_interval<V>(l, u, boost::icl::interval_bounds(bb));
        }

    template <typename Archive, typename V>
        void serialize(Archive& ar, boost::icl::discrete_interval<V>& di, unsigned v) {
            split_free(ar, di, v);
        }

    template <typename Archive, typename V>
        void save(Archive& ar, boost::icl::interval_set<V> const& is, unsigned) {
            auto sz = is.iterative_size();

            ar & sz;
            for (auto& di : is) ar & di;
        }

    template <typename Archive, typename V>
        void load(Archive& ar, boost::icl::interval_set<V>& is, unsigned) {
            is.clear();

            size_t sz;
            ar & sz;

            size_t counter = sz;

            while (counter--) {
                typename boost::icl::interval_set<V>::value_type di;
                ar & di;
                is.insert(is.end(), di);
            }

            assert(is.iterative_size() == sz);
        }

    template <typename Archive, typename V>
        void serialize(Archive& ar, boost::icl::interval_set<V>& is, unsigned v)
        {
            split_free(ar, is, v);
        }
} }

const std::string Filename = "tmp.archive";

typedef boost::icl::discrete_interval<int> Interval;
typedef boost::icl::interval_set<int> IntervalSet;

#include <fstream>
#include <string>

int main()
{
    {
        std::ofstream f(Filename);
        boost::archive::binary_oarchive oa(f);
        IntervalSet s;
        s += Interval::closed(100, 200); 
        s += Interval::left_open(30,45);
        s += Interval::right_open(77, 78);

        oa << s;
    }
    {
        std::ifstream f(Filename);
        boost::archive::binary_iarchive ia(f);

        IntervalSet s;
        ia >> s;

        std::cout << "Deserialized: ";
        std::copy(s.begin(), s.end(), std::ostream_iterator<Interval>(std::cout, " "));
    }
}
