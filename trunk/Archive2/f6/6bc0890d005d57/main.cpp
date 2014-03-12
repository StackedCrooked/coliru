#include <iostream>
#include <vector>
#include <fstream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/io/io.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>

#include <boost/geometry/algorithms/detail/has_self_intersections.hpp>

#include <boost/foreach.hpp>
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > polygon;


void union_polys(std::vector<polygon> In_polys,std::vector<polygon> &Out_polys)
{
    std::vector<polygon> temp_polys;
    bool *considered = new bool [In_polys.size()];
    for(unsigned i = 0 ; i < In_polys.size() ; i++) considered[i] = false;
    for(unsigned i = 0 ; i < In_polys.size()/2; i++)
    {
        if(!considered[i])
        {
            polygon inetr = In_polys.at(i);
            for(unsigned j = i + 1 ; j < In_polys.size() ; j++)
            {

                if(!considered[j])
                {
                    temp_polys.clear();
                    boost::geometry::union_(inetr, In_polys.at(j) , temp_polys);
                    if(temp_polys.size() == 1)
                    {
                        inetr = temp_polys.at(0);
                        considered[j] = true;
                        j = i;
                    }
                }
            }
            Out_polys.push_back(inetr);
        }
    }
}

int main()
{
    std::ifstream file("test01.txt");

    std::vector<polygon> input;

    while(!file.eof())
    {
        polygon poly;
        std::string poly_str;

        std::getline(file, poly_str);

        boost::geometry::read_wkt(poly_str, poly);
        boost::geometry::correct(poly);

        try
        {
            bool ignored = boost::geometry::detail::overlay::has_self_intersections(poly);

            // redundant:
            if (ignored)
                throw boost::geometry::overlay_invalid_input_exception();

            input.push_back(std::move(poly));
        } catch(boost::geometry::overlay_invalid_input_exception const& e)
        {
            std::cerr << "Self intersecing polygon ignored: " << boost::geometry::dsv(poly) << "\n";
        }
    }
    return 0;
    std::cout << " input size is : " << input.size() << std::endl;

    std::vector<polygon> output;
    union_polys(input, output);

    std::cout << " output size is : " << output.size() << std::endl;

    int i = 0;
    std::cout << "green || blue:" << std::endl;

    BOOST_FOREACH(polygon const& p, output)
    {
        std::cout << i++ << ": " << boost::geometry::area(p) << std::endl;
    }

    system("pause");
    return 0;
}
