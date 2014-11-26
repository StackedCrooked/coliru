#define BOOST_RESULT_OF_USE_DECTYPE
#define BOOST_SPIRIT_USE_PHOENIX_V3
    
/* virt-bmap examiner plugin
 * Copyright (C) 2014 Red Hat Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

#include <boost/icl/interval.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/interval_map.hpp>
#include <boost/container/flat_set.hpp>

using namespace std;

/* Maps intervals (uint64_t, uint64_t) to a set of strings, where each
 * string represents an object that covers that range.
 */

static size_t atoms_requested = 0;
static size_t atoms_unique_created = 0;

using string_atom = const char*;
string_atom make_atom(std::string&& s)
{
    static std::set<std::string> s_atoms;
    atoms_requested += 1;

    auto it = s_atoms.find(s);
    if (it != s_atoms.end())
        return it->c_str();

    atoms_unique_created += 1;
    return s_atoms.insert(std::move(s)).first->c_str();
}

typedef boost::container::flat_set<string_atom> objects;
typedef boost::icl::interval_map<uint64_t, objects> ranges;

ranges*
new_ranges (void)
{
  return new ranges ();
}

void
free_ranges (ranges *mapv)
{
  ranges *map = (ranges *) mapv;
  delete map;
}

extern "C" void
insert_range (void *mapv, uint64_t start, uint64_t end, const char *object)
{
  ranges *map = (ranges *) mapv;
  objects obj_set;
  obj_set.insert (obj_set.end(), object);
  map->add (std::make_pair (boost::icl::interval<uint64_t>::right_open (start, end), // SEHE added std::
                       obj_set));
}

extern "C" void
iter_range (void *mapv, void (*f) (uint64_t start, uint64_t end, const char *object, void *opaque), void *opaque)
{
  ranges *map = (ranges *) mapv;
  ranges::iterator iter = map->begin ();
  while (iter != map->end ()) {
    boost::icl::interval<uint64_t>::type range = iter->first;
    uint64_t start = range.lower ();
    uint64_t end = range.upper ();

    objects obj_set = iter->second;
    objects::iterator iter2 = obj_set.begin ();
    while (iter2 != obj_set.end ()) {
      f (start, end, *iter2/*->c_str ()*/, opaque); // SEHE
      iter2++;
    }
    iter++;
  }
}

extern "C" void
find_range (void *mapv, uint64_t start, uint64_t end, void (*f) (uint64_t start, uint64_t end, const char *object, void *opaque), void *opaque)
{
  const ranges *map = (const ranges *) mapv;

  boost::icl::interval<uint64_t>::type window;
  window = boost::icl::interval<uint64_t>::right_open (start, end);

  const ranges r = *map & window;

  ranges::const_iterator iter = r.begin ();
  while (iter != r.end ()) {
    boost::icl::interval<uint64_t>::type range = iter->first;
    uint64_t start = range.lower ();
    uint64_t end = range.upper ();

    objects obj_set = iter->second;
    objects::iterator iter2 = obj_set.begin ();
    while (iter2 != obj_set.end ()) {
      f (start, end, *iter2/*->c_str ()*/, opaque); // SEHE
      iter2++;
    }
    iter++;
  }
}

extern "C" void
find_range_ex (void *mapv, uint64_t start, uint64_t end, void (*f) (uint64_t start, uint64_t end, const char *object, void *opaque), void *opaque)
{
  const ranges *map = (const ranges *) mapv;

  boost::icl::interval<uint64_t>::type window;
  window = boost::icl::interval<uint64_t>::right_open (start, end);

#if 0
  const ranges r = *map & window;
  ranges::const_iterator iter = r.begin ();
  while (iter != r.end ()) {
#else
  auto r = map->equal_range(window);
  ranges::const_iterator iter = r.first;
  while (iter != r.second) {
#endif

    boost::icl::interval<uint64_t>::type range = iter->first;
    uint64_t start = range.lower ();
    uint64_t end = range.upper ();

    objects obj_set = iter->second;
    objects::iterator iter2 = obj_set.begin ();
    while (iter2 != obj_set.end ()) {
      f (start, end, *iter2/*->c_str ()*/, opaque); // SEHE
      iter2++;
    }
    iter++;
  }
}

#include <memory>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <fstream>
#include <chrono>

std::unique_ptr<ranges, decltype(&free_ranges)> ranges_ptr(new_ranges(), &free_ranges);
ranges& global_ranges = *ranges_ptr;
std::map<char, size_t> histo;

bool insert_line_of_input(uint64_t b, uint64_t e, char type, std::string& object) {
    if (!object.empty())
        histo[type]++;
    //std::cout << std::hex << b << " " << e << " " << type << " " << object << "\n";

#if 1
    object.insert(object.begin(), ':');
    object.insert(object.begin(), type);
#endif
    insert_range(&global_ranges, b, e, make_atom(std::move(object)));
    return true;
}

std::vector<std::pair<uint64_t, uint64_t> > generate_test_queries(size_t n) {
    std::vector<std::pair<uint64_t, uint64_t> > queries;
    queries.reserve(n);

    for (size_t i = 0; i < n; ++i)
    {
        auto start = (rand() * rand()) % global_ranges.size();
        auto end   = start + rand();

        queries.emplace_back(start,end);
    }

    return queries;
}

void read_mapfile(const char* fname) {
    std::ifstream ifs(fname);
    boost::spirit::istream_iterator f(ifs >> std::noskipws), l;

    namespace phx = boost::phoenix;
    using namespace boost::spirit::qi;
    uint_parser<uint64_t, 16> offset;
    if (!phrase_parse(f,l,
                ("1 " >> offset >> offset >> char_("pvdf") >> as_string[lexeme[+graph] >> attr('/') >> lexeme[*~char_("\r\n")]]) 
                [ _pass = phx::bind(insert_line_of_input, _1, _2, _3, _4) ] % eol >> *eol, 
                blank))
    {
        exit(255);
    } else
    {
        std::cout << "Parsed ok\n";
    }

    if (f!=l)
        std::cout << "Warning: remaining input '" << std::string(f,l) << "\n";
}

void report_statistics() {
    size_t total = 0;
    for (auto e : histo) total += e.second;

    std::cout << "Histogram of " << total << " input lines\n";

    for (auto e : histo)
        std::cout << e.first << ": " << e.second << "\n";

    namespace ba = boost::accumulators;
    ba::accumulator_set<double, ba::stats<ba::tag::mean, ba::tag::max, ba::tag::min> > 
        object_sets, interval_widths;

    for (auto const& r : global_ranges)
    {
        auto width = r.first.upper() - r.first.lower();
        assert(width % 1024 == 0);

        interval_widths(width);
        object_sets(r.second.size());
    }

    std::cout << std::fixed;
    std::cout << "ranges size:            " << global_ranges.size()                    << "\n";
    std::cout << "ranges iterative size:  " << global_ranges.iterative_size()          << "\n";

    std::cout << "Min object set:         " << ba::min(object_sets)                    << "\n" ;
    std::cout << "Max object set:         " << ba::max(object_sets)                    << "\n" ;
    std::cout << "Average object set:     " << ba::mean(object_sets)                   << "\n" ;
    std::cout << "Min interval width:     " << ba::min(interval_widths)                << "\n" ;
    std::cout << "Max interval width:     " << ba::max(interval_widths)                << "\n" ;
    std::cout << "Average interval width: " << ba::mean(interval_widths)/1024.0        << "k\n" ;
    std::cout << "First:                  " << global_ranges.begin()->first            << "\n" ;
    std::cout << "Last:                   " << global_ranges.rbegin()->first           << "\n" ;

    std::cout << "String atoms:           " << atoms_unique_created << " unique in " << atoms_requested << " total\n";
    std::cout << "Atom efficiency:        " << (atoms_unique_created*100.0/atoms_requested) << "%\n";
}

void perform_comparative_benchmarks() {
    srand(42);
    auto const queries = generate_test_queries(1000);

    using hrc = std::chrono::high_resolution_clock;
    {
        auto start = hrc::now();
        size_t callbacks = 0;

        for (auto const& q: queries)
        {
            find_range(&global_ranges, q.first, q.second, 
                    [](uint64_t start, uint64_t end, const char *object, void *opaque) {
                    ++(*static_cast<size_t*>(opaque));
                    }, &callbacks);
        }
        std::cout << queries.size() << " 'random' OLD lookups resulted in " << callbacks 
                  << " callbacks in " << std::chrono::duration_cast<std::chrono::milliseconds>((hrc::now()-start)).count() << "ms\n";
    }

    {
        auto start = hrc::now();
        size_t callbacks = 0;

        for (auto const& q: queries)
        {
            find_range_ex(&global_ranges, q.first, q.second, 
                    [](uint64_t start, uint64_t end, const char *object, void *opaque) {
                    ++(*static_cast<size_t*>(opaque));
                    }, &callbacks);
        }
        std::cout << queries.size() << " 'random' NEW lookups resulted in " << callbacks 
                  << " callbacks in " << std::chrono::duration_cast<std::chrono::milliseconds>((hrc::now()-start)).count() << "ms\n";
    }
}

int main() {
    read_mapfile("bmap.txt");

    report_statistics();

    perform_comparative_benchmarks();
#if 0 // to dump ranges to console
    for (auto const& r : global_ranges)
    {
        std::cout << r.first << "\t" << r.second.size() << "\t";
        std::copy(r.second.begin(), r.second.end(), std::ostream_iterator<std::string>(std::cout, "\t"));
        std::cout << "\n";
    }
#endif


}
