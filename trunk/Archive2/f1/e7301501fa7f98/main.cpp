#include <boost/bimap.hpp> 
#include <boost/property_map/property_map.hpp> 
#include <iostream> 

using namespace boost; 

int main() 
{
    typedef int vertex_descriptor_t;
    typedef boost::bimaps::bimap< vertex_descriptor_t, size_t > vd_idx_bimap_t;
    typedef boost::associative_property_map<vd_idx_bimap_t::left_map>   asso_vd_idx_bimap_t;

    // define bimap
    vd_idx_bimap_t        my_bimap;
    asso_vd_idx_bimap_t   my_asso_bimap(my_bimap.left);
} 
