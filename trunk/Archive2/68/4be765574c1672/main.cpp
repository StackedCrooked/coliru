#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/phoenix/function.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include <boost/range/algorithm.hpp>

namespace qi = boost::spirit::qi;
namespace bmi = boost::multi_index;
namespace phx = boost::phoenix;

struct Flight {
    std::string id, destination, gate;
    boost::posix_time::ptime departure;

    friend std::ostream& operator<<(std::ostream& os, Flight const& f) {
        return os << "'" << f.id << "'\t'" << f.destination << "'\t" << f.departure << "\t'" << f.gate << "'";
    }
};

using Flights = bmi::multi_index_container<Flight,
      bmi::indexed_by<
        bmi::ordered_unique< bmi::tag<struct by_id>, bmi::member<Flight, std::string, &Flight::id> >,
        bmi::ordered_non_unique< bmi::tag<struct by_destination>, bmi::member<Flight, std::string, &Flight::destination> >,
        bmi::ordered_non_unique< bmi::tag<struct by_departure>, bmi::member<Flight, boost::posix_time::ptime, &Flight::departure> >,
        bmi::ordered_non_unique< bmi::tag<struct by_gate>, bmi::member<Flight, std::string, &Flight::gate> >
      >
  >;

/////////////////////////////////////////////////
// input parsing

BOOST_FUSION_ADAPT_STRUCT(Flight, (std::string,id)(std::string,destination)(boost::posix_time::ptime,departure)(std::string,gate))

boost::posix_time::ptime make_departure(int a_hours, int a_minutes) {
    auto today = boost::gregorian::day_clock::local_day();

    using namespace boost::posix_time;
    auto t_o_d     = second_clock::local_time().time_of_day();
    auto departure = hours(a_hours) + minutes(a_minutes);

    return departure > (t_o_d+minutes(30))
      ? ptime { today + boost::gregorian::days(1), departure }
      : ptime { today, departure };
}

BOOST_PHOENIX_ADAPT_FUNCTION(boost::posix_time::ptime, make_departure_, make_departure, 2)

using It = boost::spirit::istream_iterator;
static const qi::rule<It, std::string()> scol              = +qi::graph;
static const qi::uint_parser<unsigned, 10, 1, 2> time_part = {};
static const qi::rule<It, boost::posix_time::ptime()> dcol = (time_part > ':' > time_part) [ qi::_val = make_departure_(qi::_1, qi::_2) ];
static const qi::rule<It, std::string()> dest_col          = +(qi::graph >> *(qi::space >> !dcol));

/////////////////////////////////////////////////
int main()
{
    std::cout << "Parsing with local date-time: " << boost::posix_time::second_clock::local_time() << "\n";

    Flights database;
    It first(std::cin >> std::noskipws), last;

    bool ok = qi::phrase_parse(first, last, qi::eps >> 
            "FLIGHT NUMBER" >> "DESTINATION" >> "DEPARTURE TIME" >> "GATE NUMBER" >> qi::eol
            >> (scol >> dest_col >> dcol >> scol) % qi::eol >> *qi::eol
            , qi::blank, database);

    if (ok) {
        std::cout << "Parse success\n";

        boost::copy(database.get<by_id>(),          std::ostream_iterator<Flight>(std::cout << "----- by flight number:\n", "\n"));
        boost::copy(database.get<by_destination>(), std::ostream_iterator<Flight>(std::cout << "----- by destination:\n", "\n"));
        boost::copy(database.get<by_departure>(),   std::ostream_iterator<Flight>(std::cout << "----- by departure time:\n", "\n"));
        boost::copy(database.get<by_gate>(),        std::ostream_iterator<Flight>(std::cout << "----- by gate:\n", "\n"));
    } else {
        std::cout << "Parse failed\n";
    }

    if (first != last)
        std::cout << "Remaining input: '" << std::string(first,last) << "'\n";
}
