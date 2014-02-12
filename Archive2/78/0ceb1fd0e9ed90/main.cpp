#include <boost/bimap.hpp> 
#include <boost/property_map/property_map.hpp> 
#include <boost/bimap/property_map/set_support.hpp>
#include <boost/bimap/list_of.hpp>
#include <iostream> 

using namespace boost; 

int main() 
{
    typedef int vertex_descriptor_t;
    namespace bm = boost::bimaps;
    typedef bm::bimap< vertex_descriptor_t, bm::list_of<size_t> > vd_idx_bimap_t;
    typedef boost::associative_property_map<vd_idx_bimap_t::left_map>   asso_vd_idx_bimap_t;

    // define bimap
    vd_idx_bimap_t        my_bimap;
    asso_vd_idx_bimap_t   my_asso_bimap(my_bimap.left);

    typedef typename vd_idx_bimap_t::value_type value_type;    
    my_bimap.insert( value_type( 1, 100 ) );

    // print bimap
    for(auto t = my_bimap.left.begin(); t != my_bimap.left.end(); ++t)
        std::cout << t->first << " " << t->second <<  "\n";

    int z = 1;
    std::cout << "value = " << get ( my_bimap.left, z ) << std::endl;    // prints correctly value = 100

    boost::put( my_asso_bimap, 2, 42 );

    for(auto t = my_bimap.left.begin(); t != my_bimap.left.end(); ++t)
        std::cout << t->first << " " << t->second <<  "\n";
 } 
