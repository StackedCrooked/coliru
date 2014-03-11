#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/assign.hpp>

#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

using namespace boost::adaptors;

typedef boost::bimap<
        boost::bimaps::multiset_of< std::string >,
        boost::bimaps::multiset_of< std::string >,
        boost::bimaps::set_of_relation<>
        > bm_type;

#include <algorithm>
#include <iterator>
#include <iostream>

struct GetRightMember
{
    template <typename> struct result { typedef std::string type; };

    template <typename T>
    std::string operator()(T const& v) const {
        return v.template get<boost::bimaps::member_at::right>();
    }
};

int main()
{
    bm_type bm;

    boost::assign::insert( bm )
        ( "John" , std::string("lazarus" ) )
        ( "Peter", std::string("vinicius") )
        ( "Peter", std::string("test") )
        ( "Simon", std::string("vinicius") )
        ( "John",  std::string("viniciusa") )
        ( "John",  std::string("vinicius") );

    const GetRightMember getright;
    std::cout << "Intersection: ";

    boost::set_intersection(
            bm.left.equal_range("John")  | transformed(getright),
            bm.left.equal_range("Peter") | transformed(getright),
            std::ostream_iterator<std::string>(std::cout, " "));
}
