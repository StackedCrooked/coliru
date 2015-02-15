#include <iostream>
#include <map>
#include <boost/regex.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_seek.hpp>

namespace boost { namespace spirit { namespace traits {
    template <typename It>
        struct assign_to_attribute_from_iterators<icl::discrete_interval<It>, It, void> {
            template <typename ... T> static void call(It b, It e, icl::discrete_interval<It>& out) {
                out = icl::discrete_interval<It>::right_open(b, e);
            }
        };
} } }

template <
    typename InputRange,
    typename It = typename boost::range_iterator<InputRange const>::type,
    typename IntervalSet = boost::icl::interval_set<It> >
IntervalSet study(InputRange const& input) {
    using std::begin;
    using std::end;

    It first(begin(input)), last(end(input));

    using namespace boost::spirit::qi;
    using boost::spirit::repository::qi::seek;

    IntervalSet variables;
    parse(first, last, *seek [ raw [ "{$" >> +char_("-a-zA-Z0-9") >> "}" ] ], variables);
    
    return variables;
}

template <
    typename InputRange,
    typename Replacements,
    typename OutputIterator,
    typename StudyMap,
    typename It = typename boost::range_iterator<InputRange const>::type
>
OutputIterator perform_replacements(InputRange const& input, Replacements const& m, StudyMap const& wisdom, OutputIterator out) 
{
    using std::begin;
    using std::end;

    It current(begin(input));

    for (auto& replace : wisdom)
    {
        It l(lower(replace)),
           u(upper(replace));

        if (current < l)
            out = std::copy(current, l, out);

        auto match = m.find({l+2, u-1});
        if (match == m.end())
            out = std::copy(l, u, out);
        else
            out = std::copy(begin(match->second), end(match->second), out);

        current = u;
    }

    if (current!=end(input))
        out = std::copy(current, end(input), out);
    return out;
}

template <
    typename InputRange,
    typename Replacements,
    typename OutputIterator,
    typename It = typename boost::range_iterator<InputRange const>::type
>
OutputIterator perform_replacements(InputRange const& input, Replacements const& m, OutputIterator out) {
    return perform_replacements(input, m, study(input), out);
}

// for demo program
#include <boost/algorithm/string.hpp>
struct ci_less {
    template <typename S>
    bool operator() (S const& a, S const& b) const {
        return boost::lexicographical_compare(a, b, boost::is_iless());
    }
};

int main()
{
    using namespace std;
    string input1 = "This {$803525c8-3ce4-423a-ad25-cc19bbe8422a} is an {$efa72abf-fe96-4983-b373-a35f70551e06} {$8a10abaa-cc0d-47bd-a8e1-34a8aa0ec1ef}!\n",
           input2 = input1;

    auto m = map<string, string> {
            { "efa72abf-fe96-4983-b373-a35f70551e06", "absolute"  },
            { "803525C8-3CE4-423A-AD25-CC19BBE8422A", "REALLY"    },
            { "8a10abaa-cc0d-47bd-a8e1-34a8aa0ec1ef", "nightmare" },
        };

    input1.erase(perform_replacements(input1, m, input1.begin()), input1.end());

    map<string, string, ci_less> im { m.begin(), m.end() };
    im["8a10abaa-cc0d-47bd-a8e1-34a8aa0ec1ef"] = "joy";

    input2.erase(perform_replacements(input2, im, input2.begin()), input2.end());

    std::cout << input1
              << input2;
}
