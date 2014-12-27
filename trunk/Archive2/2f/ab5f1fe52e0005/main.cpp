// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright (c) 2011 Barend Gehrels, Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <fstream>
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/io/io.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/foreach.hpp>

typedef boost::geometry::model::d2::point_xy<double> PointType;
using Polygon = boost::geometry::model::polygon<PointType>;

Polygon from_wkt(std::string const& wkt) {
    Polygon result;
    boost::geometry::read_wkt(wkt, result);
    return result;
}

namespace detail {

    struct do_expand {
        template <typename Box, typename Geometry>
        static inline void apply(Box& total, Geometry const& geometry) {
            boost::geometry::expand(total, boost::geometry::return_envelope<Box>(geometry));
        }
    };

    struct has_overlap {
        template <typename Box, typename Geometry>
        static inline bool apply(Box const& box, Geometry const& geometry) {
            // We're return true if the BOXES are not disjoint (box and polygon
            // might be) (this results just in a few more intersection trials in
            // the visitor, but there is no performance penalty: hardly any
            // difference if we intersect them here or there).
            return ! boost::geometry::disjoint(box, boost::geometry::return_envelope<Box>(geometry));
        }
    };

    struct intersection_visitor
    {
        std::vector<Polygon> result;

        inline void apply(Polygon const& owner, Polygon const& mr) {
            boost::geometry::model::multi_polygon<Polygon> output;
            boost::geometry::intersection(owner, mr, output);

            if (output.size() > 0) {
                std::cout << "intersect with area " << boost::geometry::area(output) << "\n";
                std::move(output.begin(), output.end(), back_inserter(result));
            }
        }
    };

    std::vector<Polygon> partitioning_intersect(std::vector<Polygon> const& lhs, std::vector<Polygon> const& rhs)
    {
        intersection_visitor visitor;

        boost::geometry::partition
            <
                boost::geometry::model::box<PointType>, do_expand, has_overlap
            >::apply(lhs, rhs, visitor, 1);

        return visitor.result;
    }

}

int main()
{
    std::vector<Polygon> lhs;
    std::vector<Polygon> rhs;

    lhs.push_back(from_wkt("POLYGON((0 0.5,0 1,0.5 1,0.5 0.5,0 0.5))"));
    lhs.push_back(from_wkt("POLYGON((0.5 0.5,0.5 1,1 1,1 0.5,0.5 0.5))"));
    lhs.push_back(from_wkt("POLYGON((0 0,0 0.5,0.5 0.5,0.5 0,0 0))"));
    lhs.push_back(from_wkt("POLYGON((0.5 0,0.5 0.5,1 0.5,1 0,0.5 0))"));

    rhs.push_back(from_wkt("POLYGON((0.25 0.75,0.25 1.25,0.75 1.25,0.75 0.75,0.25 0.75))"));
    rhs.push_back(from_wkt("POLYGON((0.75 0.75,0.75 1.25,1.25 1.25,1.25 0.75,0.75 0.75))"));
    rhs.push_back(from_wkt("POLYGON((0.25 0.25,0.25 0.75,0.75 0.75,0.75 0.25,0.25 0.25))"));
    rhs.push_back(from_wkt("POLYGON((0.75 0.25,0.75 0.75,1.25 0.75,1.25 0.25,0.75 0.25))"));

    std::cout << "n-log-n solution" << std::endl;

    auto result = detail::partitioning_intersect(lhs, rhs);

    std::cout << "Intersections: \n";
    for(auto& p : result)
        std::cout << boost::geometry::wkt(p) << "\n";
}
