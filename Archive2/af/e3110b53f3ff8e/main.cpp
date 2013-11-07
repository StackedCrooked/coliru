#include <boost/spirit/include/qi.hpp>
#include <fstream>
#include <iomanip>

namespace qi = boost::spirit::qi;

int main() {
    using namespace std;
    // read file
    ifstream ifs("input.dat", ios::binary);
    string const input { istreambuf_iterator<char>(ifs), {} };

    // parse
    vector<double> result;
    bool ret = qi::parse(begin(input), end(input), *qi::bin_double, result);

    // print
    if (ret) for (auto v : result) 
        cout << setw(28) << setprecision(16) << right << v << "\n";
}
