#include <boost/fusion/include/map.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <boost/phoenix/fusion.hpp>

namespace boost { namespace serialization {

    namespace mydetail { 
        struct saver {
            template <typename Ar, typename Pair>
                void operator()(Ar& ar, Pair& data) const {
                    ar & data.second;
                }
        };
    }

    template <typename Ar, typename... TArgs>
        void serialize(Ar& ar, boost::fusion::map<TArgs...>& fmap, unsigned /*version*/)
        {
            using phoenix::ref;
            using phoenix::arg_names::arg1;
            static const phoenix::function<mydetail::saver> save {};

            fusion::for_each(fmap, save(ref(ar), arg1));
        }

} }

#include <boost/archive/text_oarchive.hpp>
#include <iostream>

typedef boost::fusion::map<
    boost::fusion::pair<struct fieldOne, int>,
    boost::fusion::pair<struct fieldTwo, double> 
  > tFusionMap;

int main() {
    tFusionMap map { 42 , M_PI };
    boost::archive::text_oarchive oa(std::cout);
    oa & map;
}
