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

    if (!parse(first, last, *seek [ raw [ "{$" >> +alnum >> "}" ] ], variables))
        throw std::runtime_error("Parse failure at: '" + std::string(first, last) + "'");

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

namespace boost { namespace icl {
    template <typename It>
        static inline std::ostream& operator<<(std::ostream& os, discrete_interval<It> const& i) {
            return os << make_iterator_range(lower(i), upper(i));
        }
} }

int main()
{
    using namespace std;
    string const input = "This {$oops} is an {$severity} {$experience}!\n";
    auto const wisdom = study(input);

    cout << "Wisdom: ";
    for(auto& entry : wisdom)
        cout << entry;

    auto m = map<string, string> {
            { "severity",   "absolute"  },
            { "OOPS",       "REALLY"    },
            { "experience", "nightmare" },
        };

    ostreambuf_iterator<char> out(cout);
    out = '\n';

    perform_replacements(input, m, wisdom, out);

    // now let's use a case insensitive map, still with the same "study"
    map<string, string, ci_less> im { m.begin(), m.end() };
    im["eXperience"] = "joy";

    perform_replacements(input, im, wisdom, out);
}
