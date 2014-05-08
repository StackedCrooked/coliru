#include <iostream>
#include <boost/geometry.hpp>

using std::cout;
using std::endl;
namespace bg = boost::geometry;
typedef bg::model::point<float, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;
typedef bg::model::polygon<point, false, true> closed_polygon;
typedef bg::model::polygon<point, false, false> open_polygon;



int main(int argc, char * argv[])
{
    {
        closed_polygon pol;
        pol.outer().push_back(point(266.158,256));
        pol.outer().push_back(point(266.447,256.5));
        pol.outer().push_back(point(267.024,256.5));
        pol.outer().push_back(point(267.313,257));
        pol.outer().push_back(point(267.024,257.5));
        pol.outer().push_back(point(267.313,258));
        pol.outer().push_back(point(266.158,256));//you need to close the polygon
        
        double x = 222;
        double y = 257;
        cout << "Is " << bg::wkt<point>(point(x,y)) << " inside: " << ((bg::within(point(x,y),pol)) ? "yes" : "no") << endl;
        
        x = 267;
        y = 257;
        cout << "Is " << bg::wkt<point>(point(x,y)) << " inside: " << ((bg::within(point(x,y),pol)) ? "yes" : "no") << endl;
    }
    
    {
        open_polygon pol;
        pol.outer().push_back(point(266.158,256));
        pol.outer().push_back(point(266.447,256.5));
        pol.outer().push_back(point(267.024,256.5));
        pol.outer().push_back(point(267.313,257));
        pol.outer().push_back(point(267.024,257.5));
        pol.outer().push_back(point(267.313,258));
                
        double x = 222;
        double y = 257;
        cout << "Is " << bg::wkt<point>(point(x,y)) << " inside: " << ((bg::within(point(x,y),pol)) ? "yes" : "no") << endl;
        
        x = 267;
        y = 257;
        cout << "Is " << bg::wkt<point>(point(x,y)) << " inside: " << ((bg::within(point(x,y),pol)) ? "yes" : "no") << endl;
    }
    
    return 0;
}