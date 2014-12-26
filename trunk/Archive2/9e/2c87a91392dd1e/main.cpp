#include <fstream>
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/io/io.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/foreach.hpp>

typedef boost::geometry::model::d2::point_xy<double> PointType;
using Polygon = boost::geometry::model::polygon<PointType>;

Polygon MakeBox(float xmin, float ymin, float xmax, float ymax){
    Polygon poly;
    poly.outer().assign({
        {xmin, ymin},
        {xmin, ymax},
        {xmax, ymax},
        {xmax, ymin}
    });
    return poly;
}

double GetValue(const Polygon &base, const std::vector<Polygon> &polys, const std::vector<double> &vals){
    double value     = 0;
    double base_area = boost::geometry::area(base);

    boost::geometry::model::multi_polygon<Polygon> multipoly, isect, multipolynew;
    multipoly.push_back(base);

    for(size_t i=0;i<polys.size();i++){
        boost::geometry::intersection(multipoly, polys[i], isect);

        value += boost::geometry::area(isect)/base_area*vals[i];
        boost::geometry::difference(multipoly,polys[i],multipolynew);

        multipoly = multipolynew;
    }

    return value;
}

int main()
{
    Polygon base = MakeBox(0,0,10,10); //Base polygon
    std::vector<Polygon> polys;
    std::vector<double>  vals;
    //Set up some random input
    for(int i=0;i<3;i++){
        int xmin=rand()%10;
        int xmax=xmin+rand()%10;
        int ymin=rand()%10;
        int ymax=ymin+rand()%10;
        polys.push_back(MakeBox(xmin,ymin,xmax,ymax));
        vals.push_back(rand()%100);
    }
    std::cout<<GetValue(base,polys,vals)<<std::endl;
}
