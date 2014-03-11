#include <boost/bimap.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/assign.hpp>

typedef boost::bimap<
        boost::bimaps::unordered_multiset_of< std::string >,
        boost::bimaps::unordered_multiset_of< std::string >,
        boost::bimaps::set_of_relation<>
        > bm_type;

#include <algorithm>
#include <iterator>
#include <iostream>

template <typename Value = std::string, typename Bimap, typename Key>
std::set<Value> projection(Bimap const& bm, Key const& key)
{
    std::set<Value> p;
    auto range  = bm.left.equal_range(key);
    auto values = boost::make_iterator_range(range.first, range.second);

    for (auto& relation : values)
        p.insert(relation.template get<boost::bimaps::member_at::right>());

    return p;
}

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

    auto john  = projection(bm, "John");
    auto peter = projection(bm, "Peter");

    std::multiset<std::string> intersection;
    auto output = inserter(intersection, intersection.end());

    std::set_intersection(
             john.begin(), john.end(),
             peter.begin(), peter.end(),
             output
         );

    std::cout << "Intersection: ";
    for (auto const& el : intersection)
        std::cout << "'" << el << "' ";
}
