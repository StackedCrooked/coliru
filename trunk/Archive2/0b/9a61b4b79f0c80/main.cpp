#include <vector>
#include <boost/variant.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/multi/geometries/multi_polygon.hpp>
#include <boost/bind.hpp>

namespace bg = boost::geometry;

typedef bg::model::point<double, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;
typedef bg::model::polygon<point, true, true> polygon; //cw, closed polygon
typedef bg::model::multi_polygon<polygon> multipolygon;
typedef boost::variant<polygon,multipolygon> star_polygon;

struct envelope_ : boost::static_visitor<void>
{
    template <typename... T> //dispatch
    void operator()(boost::variant<T...> const& v, box& bb) const {
        boost::apply_visitor(boost::bind(*this, ::_1, boost::ref(bb)), v);
    }

    template <typename T> // relay
    void operator()(T const& v, box& bb) const {
        bg::envelope(v, bb);
    }
};

int main(void){
    static const envelope_ generic_envelope { };

    polygon staunton_county;
    bg::read_wkt("POLYGON ((-79.091666 38.132142, -79.09711 38.184771,"
        " -79.02301 38.195777, -79.049779 38.121112, -79.091666 38.132142))",
        staunton_county);

    multipolygon dickson_county;
    bg::read_wkt("MULTIPOLYGON (((-87.151995 36.289037, -87.146906 36.293344,"
        " -87.144172 36.292142, -87.142315 36.294607, -87.139332 36.292418,"
        " -87.14237199999999 36.290684, -87.151995 36.289037)),"
        " ((-87.20424199999999 35.959186, -87.53453 35.993074,"
        " -87.56679800000001 36.177857, -87.513533 36.334713,"
        " -87.286501 36.321933, -87.17730299999999 36.314145,"
        " -87.14987600000001 36.176878, -87.182573 36.049726,"
        " -87.20424199999999 35.959186)))",
        dickson_county);

    box bb;
    bg::envelope(staunton_county,bb);
    std::cout << bg::dsv(bb) << std::endl;

    bg::envelope(dickson_county,bb);;
    std::cout << bg::dsv(bb) << std::endl;

    star_polygon county;
    county = staunton_county;

    generic_envelope(county,bb);

    std::cout << bg::dsv(bb) << std::endl;

    return 0;
}
