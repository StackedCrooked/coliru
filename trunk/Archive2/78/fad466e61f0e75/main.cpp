#include <boost/geometry.hpp>
#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/io/io.hpp>
#include <fstream>
#include <iostream>

int main() {
    typedef boost::geometry::model::d2::point_xy<double> BoostPointXY;
    typedef boost::geometry::model::polygon<BoostPointXY> BoostPolygon;

    BoostPolygon polyOne, polyTwo;
    boost::geometry::read_wkt("POLYGON((45  4, 45  17, 44  19, 44  22, 50  20, 51.5  17, 58  4, 60  0, 53  0, 45  0, 45  4))", polyOne);
    boost::geometry::read_wkt("POLYGON((-10  -5, 0  25, 43  25, 45  20, 50  20, 60  0, 5  0, 5  -5, -10  -5))", polyTwo);

    boost::geometry::correct(polyOne);
    boost::geometry::correct(polyTwo);

    {
        std::ofstream svg("/tmp/svg.svg");
        boost::geometry::svg_mapper<BoostPointXY> mapper(svg, 400, 400);
        mapper.add(polyOne);
        mapper.add(polyTwo);

        mapper.map(polyOne, "fill-opacity:0.5;fill:rgb(153,204,0);stroke:rgb(153,204,0);stroke-width:2");
        mapper.map(polyTwo, "fill-opacity:0.5;fill:rgb(204,153,0);stroke:rgb(204,153,0);stroke-width:2");
    }

    std::vector<BoostPolygon> multiPoly;
    boost::geometry::intersection(polyOne,polyTwo,multiPoly);
    std::cout << "Size of Multi " << multiPoly.size() << std::endl;
}
