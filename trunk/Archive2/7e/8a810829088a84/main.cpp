#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/function/adapt_function.hpp>
#include <fstream>
#include <iomanip>

namespace qi  = boost::spirit::qi;

static inline double interpret_as_double(uint64_t binary) {
    static_assert(sizeof(double) == sizeof(uint64_t), "we can work with this");
    double val;
    std::memcpy(&val, reinterpret_cast<const char*>(&binary), sizeof(val));
    return val;
}

BOOST_PHOENIX_ADAPT_FUNCTION(double, AsDouble, interpret_as_double, 1)

typedef std::string::const_iterator It;
static const qi::rule<It, double()> binary_float = qi::qword [ qi::_val = AsDouble(qi::_1) ];

int main() {
    using namespace std;
    // read file
    ifstream ifs("input.dat", ios::binary);
    string const input { istreambuf_iterator<char>(ifs), {} };

    // parse
    vector<double> result;
    bool ret = qi::parse(begin(input), end(input), *binary_float, result);

    // print
    if (ret) for (auto v : result) 
        cout << setw(28) << setprecision(16) << right << v << "\n";
}
