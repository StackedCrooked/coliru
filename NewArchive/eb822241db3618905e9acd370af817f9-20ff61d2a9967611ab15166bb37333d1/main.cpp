#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <sstream>

using bitset = boost::dynamic_bitset<>;

// bitset helpers
int count_ranges(bitset const& bs);
std::vector<bitset> combinations(bitset const& bs);

// generate the steps script
int emit_apply_both (std::ostream& os, bitset const& edits);
int emit_toggles    (std::ostream& os, bitset const& row, std::string const& row_name);
int emit_steps      (std::ostream& os, bitset const& row1, bitset const& row2, bitset const& edits);

// applies a steps script from scratch and verifies the result 
// (optionally tracing all steps along the way)
bool verify(std::istream& is, bitset const& target1, bitset const& target2, bool verbose);

////////////////////////////////////////////////////
// The solver with a single, simple heuristic:
//
// If there's a hole in a range for row1 where row2 is to have a `1`, we might
// benefit from toggling both rows in advance, because it might result in a
// longer stretch to toggle in the first row
//
// An obvious improvement would to be to try with rows swapped as well.
//
// (As a bonus, all solutions are verified)
int solve(std::ostream& os, bitset row1, bitset row2)
{
    auto candidates = row2 & ~row1;

    int best_count = row1.size() + 1; // or INT_MAX or similar
    bitset best_edits;

    for (auto const& edits : combinations(candidates))
    {
        std::stringstream steps_stream;
        int count = emit_steps(steps_stream, row1, row2, edits);

        assert(verify(steps_stream, row1, row2, false));

        if (count < best_count)
        {
            best_edits = edits;
            best_count = count;
        }
    }

    return emit_steps(os, row1, row2, best_edits);
}

// test driver reading the target configuration from stdin
// and displaying the 'best found' solution with intermediate steps
int main()
{
    bitset row1, row2;

    if (std::cin >> row1 >> row2)
    {
        std::stringstream steps;
        int number = solve(steps, row1, row2);

        std::cout << "Best candidate found results in " << number << " steps:\n";
        verify(steps, row1, row2, true);
    }
}

////////////////////////////////////////////////////
/// details, helpers
template <typename Lambda> struct WrapAction {
    template <typename...> struct result { typedef void type; };
    template <typename... T> void operator()(T&&... t) const { _ll(std::forward<T>(t)...); }

    WrapAction(Lambda&& ll) : _ll(std::forward<Lambda>(ll)) { }
  private:
    mutable Lambda _ll;
};

template <typename Lambda> WrapAction<Lambda> make_action(Lambda&& ll) { return { std::forward<Lambda>(ll) }; }

int count_ranges(bitset const& bs)
{
    int count = 0;
    for (auto bit=bs.find_first(); bit!=bitset::npos; bit=bs.find_next(bit))
    {
        while (bs[++bit]);
        ++count;
    }
    return count;
}

std::vector<bitset> combinations(bitset const& bs)
{
    bitset accum(bs.size());
    std::vector<bitset> result;
    std::function<void(size_t bit)> recurse = [&](size_t bit) mutable 
    {
        if (bit == bitset::npos)
            result.push_back(accum);
        else
        {
            accum.flip(bit); recurse(bs.find_next(bit));
            accum.flip(bit); recurse(bs.find_next(bit));
        }
    };

    return recurse(bs.find_first()), result;
}

int emit_toggles(std::ostream& os, bitset const& row, std::string const& row_name)
{
    int count = 0;
    for (auto start=row.find_first(); start!=bitset::npos; start=row.find_next(start))
    {
        auto end = start;
        while (row[++end]);
        if (start+1 == end)
            os << "toggle " << row_name << " " << start << "\n";
        else
            os << "toggle " << row_name << " from " << start << " through " << (end-1) << "\n";
        count += 1;
        start = end;
    }
    return count;
}

int emit_apply_both(std::ostream& os, bitset const& edits)
{
    for (auto bit=edits.find_first(); bit!=bitset::npos; bit=edits.find_next(bit))
        os << "toggle both " << bit << "\n";
    return edits.count();
}

int emit_steps(std::ostream& os, bitset const& row1, bitset const& row2, bitset const& edits)
{
    auto count = emit_apply_both(os, edits);
    count     += emit_toggles   (os, row1 ^ edits, "first");
    count     += emit_toggles   (os, row2 ^ edits, "second");
    return count;
}

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
bool verify(std::istream& is, bitset const& target1, bitset const& target2, bool verbose)
{
    bitset row1(target1.size()), row2(target2.size());
    if (verbose) std::cout << "Start verify\n";

    auto toggle1 = make_action([&](int i) mutable { row1.flip(i); });
    auto toggle2 = make_action([&](int i) mutable { row2.flip(i); });
    auto both    = make_action([&](int i) mutable { toggle1(i); toggle2(i); });
    auto range1  = make_action([&](int i1, int i2) mutable { while (i2>=i1) toggle1(i2--); });
    auto range2  = make_action([&](int i1, int i2) mutable { while (i2>=i1) toggle2(i2--); });
    
    // for statement tracing:
    typedef boost::spirit::istream_iterator It;
    auto trace = make_action([&](boost::iterator_range<It> const& raw_iterators) mutable {
                if (verbose) {
                    std::cout << "after '" << std::string(raw_iterators.begin(), raw_iterators.end()) << "':\n";
                    std::cout << "  row1:\t" << row1 << "\n" << "  row2:\t" << row2 << "\n"; 
                }
            });

    using namespace boost::spirit::qi;
    namespace phx = boost::phoenix;
    using phx::bind;
    using phx::construct;

    is.unsetf(std::ios::skipws);
    It f(is), l;
    bool ok = phrase_parse(f, l,
            - raw [  
                lit("toggle") >> ("both" >> int_)                                       [ bind(both, _1)       ]
              | lit("toggle") >> lit("first")  >> ("from" >> int_ >> "through" >> int_) [ bind(range1, _1, _2) ]
              | lit("toggle") >> lit("second") >> ("from" >> int_ >> "through" >> int_) [ bind(range2, _1, _2) ]
              | "toggle"      >> lit("first")  >> (int_)                                [ bind(toggle1,  _1)   ]
              | "toggle"      >> lit("second") >> (int_)                                [ bind(toggle2,  _1)   ]
              | eps(false)
             ] [ bind(trace, _1) ] % eol,
            blank);

    if (verbose)
    {
        if (ok)     std::cout << "Done\n";
        else        std::cout << "Failed\n";
        if (f != l) std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
    }

    return ok && (f==l) && (row1==target1) && (row2==target2);
}

