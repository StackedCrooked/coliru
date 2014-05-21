#include <boost/icl/split_interval_set.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <iostream>
#include <map>

namespace icl = boost::icl;
using boost::adaptors::map_values;

typedef icl::split_interval_set<int> iset;
typedef std::map<int, iset> iset_map;

template <typename C>
    iset_map transpose_input(C const& raw_input)
{
    iset_map trans;

    for(typename C::const_iterator it = raw_input.begin(); it != raw_input.end(); ++it)
        for (size_t i = 0; i<it->size(); ++i)
            trans[i].insert(it->at(i));

    return trans;
}

int main()
{
    typedef iset::interval_type ival;
    typedef std::vector<ival> ival_vec;
    // for parsing
    typedef boost::spirit::istream_iterator input;

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

    iset_map const transposed = transpose_input(raw_input);
    iset unioned;
    for (iset_map::const_iterator it = transposed.begin(); it != transposed.end(); ++it)
        boost::copy(it->second, std::inserter(unioned, unioned.end()));

    for (iset::const_iterator iv = unioned.begin(); iv != unioned.end(); ++iv) {
        for (iset_map::const_iterator pair = transposed.begin(); pair != transposed.end(); ++pair)
        {
            iset const& set = pair->second;
            size_t idx = distance(set.begin(), set.lower_bound(*iv));

            std::cout << *iv << " (" << (idx+1) << ")\t|";
        }
        std::cout << "\n";
    }
}
