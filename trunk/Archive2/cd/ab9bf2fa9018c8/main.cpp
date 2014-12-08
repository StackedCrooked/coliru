#include <iostream>
#include <deque>
#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>
#include <boost/geometry/io/svg/write_svg.hpp>
#include <boost/geometry/algorithms/append.hpp>

#include <algorithm> // for reverse, unique
#include <iostream>
#include <string>
#include <fstream>

template <typename Geometry1, typename Geometry2>
void create_svg(std::string const& filename, Geometry1 const& a, Geometry2 const& b)
{
    typedef typename boost::geometry::point_type<Geometry1>::type point_type;
    std::ofstream svg(filename.c_str());

    boost::geometry::svg_mapper<point_type> mapper(svg, 400, 400);
    mapper.add(a);
    mapper.add(b);

    mapper.map(a, "fill-opacity:0.5;fill:rgb(153,204,0);stroke:rgb(153,204,0);stroke-width:0.01");
    mapper.map(b, "opacity:0.8;fill:none;stroke:rgb(255,128,0);stroke-width:0.01;stroke-linecap:round");
}

int main()
{
   typedef boost::geometry::model::d2::point_xy<long long,    boost::geometry::cs::cartesian> point_2d;
   typedef boost::geometry::model::polygon<point_2d> polygon_2d;

    polygon_2d green;

    boost::geometry::append(green, point_2d(2861880L,  909575L));
    boost::geometry::append(green, point_2d(2749020L,  562215L));
    boost::geometry::append(green, point_2d(2742380L,  557393L));
    boost::geometry::append(green, point_2d(2469080L,  519765L));
    boost::geometry::append(green, point_2d(1944770L,  597441L));
    boost::geometry::append(green, point_2d(1592130L, 1011410L));
    boost::geometry::append(green, point_2d(2035760L, 1495370L));
    boost::geometry::append(green, point_2d(2861880L,  909575L));


    polygon_2d blue;
    boost::geometry::append(blue, point_2d(2400000L,  530000L));
    boost::geometry::append(blue, point_2d(2400000L, -530000L));
    boost::geometry::append(blue, point_2d(-600000L, -530000L));
    boost::geometry::append(blue, point_2d(-600000L,  530000L));
    boost::geometry::append(blue, point_2d(2400000L,  530000L));

    boost::geometry::correct(green);
    boost::geometry::correct(blue);

    std::vector<polygon_2d> output;
    boost::geometry::intersection(green, blue, output);

    create_svg("test.svg", green, blue);
    if(output.size())
    {
        std::cout << "green && blue:" << std::endl;
        std::cout<<boost::geometry::dsv(output[0])<<std::endl;
        std::cout<<boost::geometry::area(output[0])<<std::endl;
    }

    return 0;
}
