#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/io/io.hpp>
#include <boost/geometry/io/wkt/stream.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/algorithms/correct.hpp>

#include <iomanip>
#include <fstream>
#include <iostream>

#if 0
#include <boost/multiprecision/cpp_dec_float.hpp>
typedef boost::multiprecision::cpp_dec_float<50> dec_float_backend;
typedef boost::multiprecision::number<dec_float_backend, boost::multiprecision::expression_template_option::et_off> T;
#else
typedef int T;
#endif

typedef boost::geometry::model::point<T, 3, boost::geometry::cs::cartesian> boostPoint;
typedef boost::geometry::model::segment<boostPoint> boostSegment;

int main() {
    std::cout << std::setprecision(std::numeric_limits<double>::max_digits10+2);

    for (auto&& segments : {
                // a simple test with intersection [ 5,0,0 ]
                std::make_pair(
                    boostSegment(boostPoint(0 , 0 , 0), boostPoint(10, 0 , 0)),
                    boostSegment(boostPoint(+3, +1, 0), boostPoint(+7, -1, 0))
                ),
                // the test from the OP:
                std::make_pair(
                    boostSegment(boostPoint(0, 0, 0), boostPoint(2, 0, 0)),
                    boostSegment(boostPoint(1, 1, 2), boostPoint(1, -1, 2))
                ),
            })
    {
        std::vector<boostPoint> output;
        boost::geometry::correct(segments.first); // just in case o.O
        boost::geometry::correct(segments.second);
        boost::geometry::intersection(segments.first, segments.second, output);

        std::cout << "Intersecting " << segments.first << " and " << segments.second << "\n";
        std::cout << "Output size: " << output.size() << " ";
        if (!output.empty()) std::cout << output[0];
        std::cout << "\n";
    }
}