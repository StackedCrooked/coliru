#include <boost/bimap.hpp> 
#include <boost/property_map/property_map.hpp> 
#include <boost/bimap/property_map/set_support.hpp>
#include <boost/bimap/list_of.hpp>
#include <iostream> 
using namespace boost; 
int main() {
typedef int vertex_descriptor_t;
namespace bm = boost::bimaps;
typedef bm::bimap< bm::list_of<vertex_descriptor_t>, bm::list_of<size_t> > vd_idx_bimap_t;
//typedef boost::associative_property_map<vd_idx_bimap_t::left_map>    Lasso_vd_idx_bimap_t;
typedef boost::associative_property_map<vd_idx_bimap_t::right_map>   Rasso_vd_idx_bimap_t;

// define bimap and assoc prop map for it
vd_idx_bimap_t        my_bimap;
//Lasso_vd_idx_bimap_t  Lmy_asso_bimap(my_bimap.left );
Rasso_vd_idx_bimap_t  Rmy_asso_bimap(my_bimap.right);

typedef typename vd_idx_bimap_t::value_type value_type;    
my_bimap.insert( value_type( 1, 100 ) );
my_bimap.insert( value_type( 2, 200 ) );

//int z = 1;
//std::cout << "value = " << get ( my_bimap.left, z ) << std::endl;    // prints correctly value = 100

// use left asso bimap for inserting to bimap 
boost::put( Rmy_asso_bimap, 3, 300 );

// print bimap using left view
//for(auto t = my_bimap.left.begin(); t != my_bimap.left.end(); ++t)
 //   std::cout << t->first << " " << t->second <<  "\n";

int y = 2;
z = boost::get( Rmy_asso_bimap, y  );
std::cout << "value = " << z << std::endl;

// Use right asso bimap to get key based on supplied value
y = 100;
z = boost::get( Rmy_asso_bimap, y );    // -->> error here 
std::cout << "value = " << z << std::endl;

// print map again. (right view)
for(auto t = my_bimap.right.begin(); t != my_bimap.right.end(); ++t)
    std::cout << t->first << " " << t->second <<  "\n";

} 