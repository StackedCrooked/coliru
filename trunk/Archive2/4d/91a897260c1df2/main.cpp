#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <fstream>
#include <iterator>

namespace qi = boost::spirit::qi;

struct DataPoint
{
    int id1;
    int id2;
    int day;
    int month;
    int year;
    int shift;
    int hour;
    int minute;
//  int width;
//  int fraction;
//  int numbs;
};

BOOST_FUSION_ADAPT_STRUCT(DataPoint, (int, id1)(int, id2)(int, day)(int, month)(int, year)(int, shift)(int, hour)(int, minute))

      //(int, width)
      //(int, fraction)
      //(int, numbs)

int main()
{
    std::ifstream machine_samples_1("filename");
    machine_samples_1.unsetf(std::ios::skipws);

    boost::spirit::istream_iterator first(machine_samples_1), last; 

    using qi::int_;
    std::vector<DataPoint> datapoints;
    bool ok = qi::phrase_parse(
            first, last, // input range
            (int_ >> int_ >> int_ >> int_ >> int_ >> int_ >> int_ >> int_) % qi::eol, // grammar
            qi::blank, // skipper
            datapoints);

    std::cout << "Parsed " << datapoints.size() << " data points";
}
