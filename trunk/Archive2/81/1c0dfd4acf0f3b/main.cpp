#include <boost/regex.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

namespace qi = boost::spirit::qi;
namespace io = boost::iostreams;
using sref   = boost::string_ref;
using regex  = boost::regex;

namespace boost { namespace spirit { namespace traits {
    template <typename It>
    struct assign_to_attribute_from_iterators<sref, It, void> {
        static void call(It f, It l, sref& attr) { attr = { f, size_t(std::distance(f,l)) }; }
    };
} } }

typedef std::map<std::string::difference_type, sref> hitmap;
hitmap hits;

void regres(const boost::match_results<const char*>& what) {
    hits[what.position()] = sref(what[0].first, what[0].length());
}

int main() {
    std::vector<sref> wordlist;
    {
        io::mapped_file_source mapped("/etc/dictionaries-common/words");
        qi::parse(mapped.begin(), mapped.end(), qi::raw[+(qi::char_ - qi::eol)] % qi::eol, wordlist);
    }

    std::cout << "Wordlist contains " << wordlist.size() << " entries\n";

    io::mapped_file_source book("/etc/dictionaries-common/words");

    for (auto const& s: wordlist) {
        regex word(s.to_string());
        boost::cregex_iterator lex(book.begin(), book.end(), word), end;
        std::for_each(lex, end, &regres);
    }
}
