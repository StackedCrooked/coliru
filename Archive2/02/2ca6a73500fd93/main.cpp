#include <boost/icl/split_interval_set.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <iostream>
#include <map>

namespace icl = boost::icl;
using boost::adaptors::map_values;

using iset = icl::split_interval_set<int>;

template <typename C>
    std::map<int, iset> transpose_input(C const& raw_input)
{
    std::map<int, iset> trans;

    for(auto& line : raw_input)
        for (size_t i = 0; i<line.size(); ++i)
            trans[i].insert(line[i]);

    return trans;
}

int main()
{
    using ival     = iset::interval_type;
    using ival_vec = std::vector<ival>;
    // for parsing
    using input    = boost::spirit::istream_iterator;

    std::vector<ival_vec> raw_input;
    {
        using namespace boost::spirit::qi;
        using boost::phoenix::construct;

        input f(std::cin >> std::noskipws), l;
        rule<input, iset::interval_type(), blank_type> ival_ 
            = ('[' >> int_ >> '-' >> int_ >> ']') [ _val = construct<ival>(_1, _2) ]
            | eps;

        bool ok = phrase_parse(f, l, ival_ % '|' % eol, blank, raw_input);

        if (!ok || f!=l) {
            std::cout << "unparsed: '" << std::string(f,l) << "'\n";
            return 255;
        }
    }

    auto const transposed = transpose_input(raw_input);
    iset unioned;
    for (auto& set : transposed | map_values)
        boost::copy(set, std::inserter(unioned, unioned.end()));

    for (auto const& iv : unioned) {
        for(auto const& pair : transposed) {
            auto& set = pair.second;
            auto idx = distance(set.begin(), set.lower_bound(iv));

            std::cout << iv << " (" << (idx+1) << ")\t|";
        }
        std::cout << "\n";
    }
}
