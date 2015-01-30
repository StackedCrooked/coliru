#define NDEBUG
#undef DEBUG
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/container/flat_map.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/spirit/include/qi.hpp>
#include <iomanip>

namespace bip = boost::interprocess;
namespace qi = boost::spirit::qi;

namespace shared {
    namespace bc = boost::container;

    template <typename T> using allocator = bip::allocator<T, bip::managed_mapped_file::segment_manager>;
    template <typename K, typename V>
        using multi_map = bc::flat_multimap<
            K, V, std::less<K>, 
            allocator<typename bc::flat_multimap<K, V>::value_type> >;
}

#include <iostream>

bip::managed_mapped_file msm(bip::open_or_create, "lookup.bin", /*10ul<<30*/ 10*1024);

template <typename K, typename V>
shared::multi_map<K,V>& get_or_load(const char* fname) {
    using Map = shared::multi_map<K, V>;
    Map* lookup = msm.find_or_construct<Map>("lookup")(msm.get_segment_manager());

    if (lookup->empty()) { 
        // only read input file if not already loaded
        boost::iostreams::mapped_file_source input(fname);
        auto f(input.data()), l(f + input.size());

        bool ok = qi::phrase_parse(f, l,
                (qi::auto_ >> qi::auto_) % qi::eol >> *qi::eol, 
                qi::blank, *lookup);

        if (!ok || (f!=l))
            throw std::runtime_error("Error during parsing at position #" + std::to_string(f - input.data()));
    }

    return *lookup;
}

int main() {
    // parse text file into shared memory binary representation
    auto const& lookup = get_or_load<double, unsigned int>("input.txt");
    auto const e = lookup.end();

    for(auto&& line : lookup)
    {
        std::cout << line.first << "\t" << line.second << "\n";

        auto er = lookup.equal_range(line.first);

        if (er.first  != e) std::cout << " lower: " << er.first->first  << "\t" << er.first->second  << "\n";
        if (er.second != e) std::cout << " upper: " << er.second->first << "\t" << er.second->second << "\n";
    }
}
