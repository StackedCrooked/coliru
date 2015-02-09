#include <boost/fusion/include/at_key.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/pair.hpp>

struct A { };
struct B { };

int main()
{
    boost::fusion::map<
        boost::fusion::pair<
            A, 
            boost::fusion::map<boost::fusion::pair<unsigned int, B> >
        >
    > map_;

    B b = boost::fusion::at_key<unsigned int>(boost::fusion::at_key<A>(map_));
}
